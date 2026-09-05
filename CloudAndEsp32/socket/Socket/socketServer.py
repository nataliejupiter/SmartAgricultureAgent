# 服务端程序

import socket
import base64
import hashlib
import threading

class WebSocketServer():
    def __init__(self,host:str,port:int):
        self.BUFLEN = 1024
        self.host = host
        self.port = port
        self.Websocket = socket.socket()
        self.Websocket.bind((host,port))  # 这里的host和port是客户端设备地址、端口
        self.Websocket.listen()  # 使socket处于监听状态，等待客户端连接
        print("服务端启动成功，等待连接...")
        self.listenthread = threading.Thread(target=self.listenWebSocket)
        self.listenthread.start()

    def listenWebSocket(self) -> None:
        dataSocket, address = self.Websocket.accept() # 轮询，阻塞等待连接，dataSocket用于传输数据，addr为客户端IP
        print(f"已连接客户端，IP是{address}")
        # WebsocketClient = Websocket(fileno=dataSocket.fileno())
        # dealThread = threading.Thread(target=self.deal_Thread,args=(WebsocketClient,address))
        # dealThread.start()

        #尝试读取对方发送的消息，BUFLEN制定从接收缓冲里最多读取多少字节
        while True:
            recved = dataSocket.recv(self.BUFLEN) # 阻塞

            # 如果返回空bytes，表示对方关闭了连接
            if not recved:
                break

            # 读取的字节数据是bytes类型，需要解码成字符串
            info = recved.decode()
            print(f"收到对方的消息：{info}")

            # 发送的数据类型必须是bytes类型，需要编码
            dataSocket.send(info.encode())

    # def deal_Thread(self,dataSocket:socket.socket, address:str):
    #         print(dataSocket.recv(1024))

class Websocket(socket.socket):
    WEBSOCKET_GUID = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"
    # 定义WebSocket握手的GUID

    def __init__(self, family: socket.AddressFamily | int = -1, type: socket.SocketKind | int = -1, proto: int = -1, fileno: int | None = None) -> None:
        super().__init__(family, type, proto, fileno)
        self.handshake()
        pass

    # 尝试读取对方发送的信息，__bufSize指定从缓冲里最多读取多少字节
    # 传输的是字节串
    def Receive(self,__bufSize:int) -> bytes:
        return super().recv(__bufSize)
    
    def recv(self, __bufsize: int) -> bytes:
        Data = self.Receive(__bufsize)
        return self.decode_frame(Data)
    
    # 处理WebSocket握手
    def handshake(self):
        request = self.Receive(1024).decode('utf-8')
        headers = {}
        for line in request.split("\r\n")[1:]:
            if ": " in line:
                key, value = line.split(": ", 1)
                headers[key] = value

        if "Sec-WebSocket-Key" in headers:
            key = headers["Sec-WebSocket-Key"]
            accept_key = base64.b64encode(hashlib.sha1((key + Websocket.WEBSOCKET_GUID).encode()).digest()).decode('utf-8')
            response = (
                "HTTP/1.1 101 Switching Protocols\r\n"
                "Upgrade: websocket\r\n"
                "Connection: Upgrade\r\n"
                f"Sec-WebSocket-Accept: {accept_key}\r\n\r\n"
            )
            self.send(response.encode('utf-8'))

    # 读取的字节数据是bytes类型，需要接码成字符串
    def decode_frame(self,data):
        payload_length = data[1] & 127
        # 根据 WebSocket 协议调整长度解析逻辑
        if payload_length == 126:
            payload_length = int.from_bytes(data[2:4], byteorder='big')
            mask_start = 4
        elif payload_length == 127:
            payload_length = int.from_bytes(data[2:10], byteorder='big')
            mask_start = 10
        else:
            mask_start = 2
        mask = data[mask_start:mask_start + 4]
        payload_start = mask_start + 4
        payload = data[payload_start:payload_start + payload_length]
        decoded = bytes([payload[i] ^ mask[i % 4] for i in range(len(payload))])
        return decoded
    
if __name__ == "__main__":
    #import time
    WebSocketServer("0.0.0.0",25564)
    # time.sleep(10000)



