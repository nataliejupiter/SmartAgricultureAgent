#!/usr/bin/env python3
"""
python sttStream.py --model /userdata/llmAndGRU/ttsAndStt/models/Systran/faster-whisper-base --device cpu --compute-type int8 --language zh

Real-time / near-real-time microphone STT with faster-whisper.

Core idea:
- microphone callback captures 16 kHz mono audio continuously
- a lightweight energy VAD decides when speech starts/ends
- while speech is active, the script periodically transcribes the
  accumulated utterance buffer with faster-whisper
- only the stable prefix is printed during speech; the final result is
  confirmed after silence

This is practical low-latency streaming, not true token-by-token streaming.
"""

from __future__ import annotations

import argparse
import queue
import threading
import time
from collections import deque
from dataclasses import dataclass
from typing import Deque, Optional

import numpy as np
import sounddevice as sd
from faster_whisper import WhisperModel


SAMPLE_RATE = 16_000
CHANNELS = 1
DTYPE = "float32"

# Audio / VAD tuning
BLOCK_MS = 100                 # callback block size in milliseconds
PRE_ROLL_SECONDS = 0.4         # keep a little audio before speech starts
MIN_SPEECH_SECONDS = 0.25      # avoid triggering on accidental noise
END_SILENCE_SECONDS = 0.8      # silence gap to finalize an utterance
POLL_SECONDS = 0.5             # transcribe every N seconds during speech
MAX_UTTERANCE_SECONDS = 18.0   # prevent one utterance from growing forever

# Energy VAD threshold. Tune for your microphone and room noise.
# Typical starting range: 0.008 ~ 0.02
RMS_THRESHOLD = 0.012
RMS_HYSTERESIS = 0.004


@dataclass
class AudioChunk:
    data: np.ndarray
    ts: float


def rms_energy(x: np.ndarray) -> float:
    if x.size == 0:
        return 0.0
    return float(np.sqrt(np.mean(np.square(x), dtype=np.float64)))


def normalize_text(text: str) -> str:
    text = text.replace("\u3000", " ")
    text = " ".join(text.split())
    return text.strip()


def common_prefix(a: str, b: str) -> str:
    n = min(len(a), len(b))
    i = 0
    while i < n and a[i] == b[i]:
        i += 1
    return a[:i]


class RealTimeSTT:
    def __init__(
        self,
        model_name: str = "small",
        device: str = "cpu",
        compute_type: str = "int8",
        language: str = "zh",
        beam_size_partial: int = 1,
        beam_size_final: int = 5,
    ) -> None:
        self.model_name = model_name
        self.device = device
        self.compute_type = compute_type

        self.model = WhisperModel(model_name, device=device, compute_type=compute_type)
        self.language = language
        self.beam_size_partial = beam_size_partial
        self.beam_size_final = beam_size_final

        self.audio_q: "queue.Queue[AudioChunk]" = queue.Queue(maxsize=200)
        self.stop_event = threading.Event()

        self.prebuffer: Deque[np.ndarray] = deque()
        self.prebuffer_samples = int(PRE_ROLL_SECONDS * SAMPLE_RATE)

        self.in_speech = False
        self.awaiting_final = False
        self.speech_started_at: Optional[float] = None
        self.last_voice_at: Optional[float] = None
        self.last_partial_at: float = 0.0
        self.speech_frames: list[np.ndarray] = []

        self.current_committed = ""
        self.previous_hypothesis = ""

        self.pending_lock = threading.Lock()
        self.pending_event = threading.Event()
        self.pending_audio: Optional[np.ndarray] = None
        self.pending_job_id: int = 0
        self.pending_final: bool = False
        self.latest_job_id: int = 0

        self.audio_thread = threading.Thread(target=self._audio_consumer_loop, daemon=True)
        self.worker_thread = threading.Thread(target=self._transcribe_worker_loop, daemon=True)

    def start(self) -> None:
        self.audio_thread.start()
        self.worker_thread.start()

    def stop(self) -> None:
        self.stop_event.set()
        self.pending_event.set()

    def _audio_callback(self, indata, frames, time_info, status) -> None:
        if status:
            pass
        chunk = np.array(indata[:, 0], dtype=np.float32, copy=True)
        try:
            self.audio_q.put_nowait(AudioChunk(data=chunk, ts=time.monotonic()))
        except queue.Full:
            try:
                _ = self.audio_q.get_nowait()
            except queue.Empty:
                pass
            try:
                self.audio_q.put_nowait(AudioChunk(data=chunk, ts=time.monotonic()))
            except queue.Full:
                pass

    def _append_prebuffer(self, chunk: np.ndarray) -> None:
        self.prebuffer.append(chunk)
        total = sum(x.shape[0] for x in self.prebuffer)
        while total > self.prebuffer_samples and self.prebuffer:
            removed = self.prebuffer.popleft()
            total -= removed.shape[0]

    def _current_utterance_audio(self) -> np.ndarray:
        frames = list(self.prebuffer) + self.speech_frames
        if not frames:
            return np.zeros((0,), dtype=np.float32)
        return np.concatenate(frames, axis=0)

    def _request_transcribe(self, final: bool) -> None:
        audio = self._current_utterance_audio()
        if audio.size < int(MIN_SPEECH_SECONDS * SAMPLE_RATE):
            return

        with self.pending_lock:
            self.latest_job_id += 1
            self.pending_job_id = self.latest_job_id
            self.pending_audio = audio
            self.pending_final = final
            self.pending_event.set()

    def _audio_consumer_loop(self) -> None:
        while not self.stop_event.is_set():
            try:
                item = self.audio_q.get(timeout=0.1)
            except queue.Empty:
                item = None

            now = time.monotonic()

            if item is None:
                if self.in_speech and self.last_voice_at is not None:
                    if (now - self.last_voice_at) >= END_SILENCE_SECONDS and not self.awaiting_final:
                        self.awaiting_final = True
                        self._request_transcribe(final=True)
                        self._print_line("\n[检测到停顿，正在确认最终结果...]")
                continue

            chunk = item.data
            level = rms_energy(chunk)

            self._append_prebuffer(chunk)

            speech_on = level >= RMS_THRESHOLD
            speech_keep = level >= (RMS_THRESHOLD - RMS_HYSTERESIS)

            if not self.in_speech:
                if speech_on:
                    self.in_speech = True
                    self.awaiting_final = False
                    self.speech_started_at = now
                    self.last_voice_at = now
                    self.last_partial_at = 0.0
                    self.speech_frames = list(self.prebuffer)
                    self.current_committed = ""
                    self.previous_hypothesis = ""
                    self._print_line("\n[开始识别]")
                    self.speech_frames.append(chunk)
            else:
                self.speech_frames.append(chunk)

                if speech_keep:
                    self.last_voice_at = now

                if now - self.last_partial_at >= POLL_SECONDS and not self.awaiting_final:
                    self.last_partial_at = now
                    self._request_transcribe(final=False)

                if self.speech_started_at is not None and (now - self.speech_started_at) >= MAX_UTTERANCE_SECONDS:
                    if not self.awaiting_final:
                        self.awaiting_final = True
                        self._request_transcribe(final=True)
                        self._print_line("\n[语音过长，正在截断并确认结果...]")

                if self.last_voice_at is not None and (now - self.last_voice_at) >= END_SILENCE_SECONDS:
                    if not self.awaiting_final:
                        self.awaiting_final = True
                        self._request_transcribe(final=True)
                        self._print_line("\n[句子结束，正在确认最终结果...]")

    def _transcribe_worker_loop(self) -> None:
        while not self.stop_event.is_set():
            self.pending_event.wait(timeout=0.1)
            if self.stop_event.is_set():
                break

            with self.pending_lock:
                audio = self.pending_audio
                job_id = self.pending_job_id
                final = self.pending_final
                self.pending_audio = None
                self.pending_event.clear()

            if audio is None:
                continue

            try:
                text = self._run_transcribe(audio=audio, final=final)
            except Exception as e:
                text = f"[转写失败: {e}]"

            if job_id != self.latest_job_id:
                continue

            self._consume_transcript(text=text, final=final)

    def _run_transcribe(self, audio: np.ndarray, final: bool) -> str:
        if audio.size == 0:
            return ""

        beam_size = self.beam_size_final if final else self.beam_size_partial

        segments, _info = self.model.transcribe(
            audio,
            language=self.language,
            vad_filter=True,
            vad_parameters=dict(min_silence_duration_ms=500),
            chunk_length=5,
            beam_size=beam_size,
            best_of=max(beam_size, 1),
            temperature=0.0,
            condition_on_previous_text=False,
            word_timestamps=False,
            initial_prompt=None,
        )

        texts = []
        for seg in segments:
            t = normalize_text(seg.text)
            if t:
                texts.append(t)

        return normalize_text(" ".join(texts))

    def _consume_transcript(self, text: str, final: bool) -> None:
        text = normalize_text(text)
        if not text:
            if final:
                self._reset_utterance()
            return

        if not self.previous_hypothesis:
            self.previous_hypothesis = text
            if final:
                self.current_committed = text
                self._print_final(text)
                self._reset_utterance()
            return

        stable = common_prefix(self.previous_hypothesis, text)

        if len(stable) > len(self.current_committed):
            delta = stable[len(self.current_committed):]
            self.current_committed = stable
            if delta:
                self._print_partial(delta)

        self.previous_hypothesis = text

        if final:
            if len(text) > len(self.current_committed):
                tail = text[len(self.current_committed):]
                if tail:
                    self.current_committed = text
                    self._print_partial(tail)
            self._print_final("")
            self._reset_utterance()

    def _reset_utterance(self) -> None:
        self.in_speech = False
        self.awaiting_final = False
        self.speech_started_at = None
        self.last_voice_at = None
        self.last_partial_at = 0.0
        self.speech_frames = []
        self.prebuffer.clear()
        self.current_committed = ""
        self.previous_hypothesis = ""

    @staticmethod
    def _print_partial(text: str) -> None:
        if text:
            print(text, end="", flush=True)

    @staticmethod
    def _print_final(text: str) -> None:
        if text:
            print(text, end="", flush=True)
        print("", flush=True)

    @staticmethod
    def _print_line(text: str) -> None:
        print(text, flush=True)

    def run(self, device_index: Optional[int] = None) -> None:
        self.start()

        self._print_line(
            f"🎤 启动成功：model={self.model_name}, device={self.device}, "
            f"compute_type={self.compute_type}, sample_rate={SAMPLE_RATE}, "
            f"block={BLOCK_MS}ms, threshold={RMS_THRESHOLD}, language={self.language}"
        )
        self._print_line("按 Ctrl+C 退出。")

        blocksize = int(SAMPLE_RATE * BLOCK_MS / 1000)

        try:
            with sd.InputStream(
                samplerate=SAMPLE_RATE,
                channels=CHANNELS,
                dtype=DTYPE,
                blocksize=blocksize,
                device=device_index,
                callback=self._audio_callback,
            ):
                while True:
                    time.sleep(0.2)
        except KeyboardInterrupt:
            self._print_line("\n退出中...")
        finally:
            self.stop()
            time.sleep(0.3)


def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser()
    p.add_argument("--model", type=str, default="small", help="tiny/base/small/medium/large-v3 等")
    p.add_argument("--device", type=str, default="cpu", choices=["cpu", "cuda", "auto"])
    p.add_argument("--compute-type", type=str, default="int8", help="cpu 常用 int8；cuda 常用 float16 或 int8_float16")
    p.add_argument("--language", type=str, default="zh", help="固定语言可减少额外开销，如 zh/en")
    p.add_argument("--beam-partial", type=int, default=1, help="实时阶段 beam size")
    p.add_argument("--beam-final", type=int, default=5, help="句子结束后的最终确认 beam size")
    p.add_argument("--device-index", type=int, default=None, help="麦克风设备编号，不填则使用默认设备")
    return p.parse_args()


def main() -> None:
    args = parse_args()
    stt = RealTimeSTT(
        model_name=args.model,
        device=args.device,
        compute_type=args.compute_type,
        language=args.language,
        beam_size_partial=args.beam_partial,
        beam_size_final=args.beam_final,
    )
    stt.run(device_index=args.device_index)


if __name__ == "__main__":
    main()
