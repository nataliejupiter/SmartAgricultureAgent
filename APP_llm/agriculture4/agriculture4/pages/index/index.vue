<template>
	
	<view class="search-container">
		<!-- 搜索框 -->
		<view class="search-input-wrapper">
			<input 
				v-model="searchText" 
				type="text" 
				placeholder="请输入搜索内容" 
				class="search-input"
			/>
			<view v-if="searchText" class="clear-icon" @click="clearInput">✖</view>
			
		</view>
		
		<!-- 发送按钮 -->
		<button 
			class="send-btn" 
			@click="handleSend"
			:disabled="!searchText.trim() || isLoading"
		>
			{{ isLoading ? '生成中...' : '发送' }}
		</button>
		<!-- 历史查询按钮-->
		<button
	    class="history-btn"
		@click="goToHistory"
		>
		历史查询	
		</button>
		
	</view>
	
	<!-- 答案展示区 -->
	<view class="answer-container">
		<view class="answer-title">
			结果：
		</view>
		<view class="action-buttons">
			 <button v-if="aiAnswer" class="voice-btn" @click="speakAnswer" :disabled="isSpeaking">🔊 朗读</button>
			
			<button v-if="aiAnswer" class="copy-btn" @click="copyAnswer">复制</button>
			
		</view>
		<button class="knowledge-btn" @click="goToKnowledge">知识管理</button>
		<view class="answer-content-wrapper" v-if="aiAnswer">
		  <text class="answer-text">{{ aiAnswer }}</text>
		  <text class="collect-plus" @click.stop="collectAnswer">＋</text>
		</view>
		<view class="empty-tip" v-else-if="!isLoading">
			暂无内容，请先发送问题
		</view>
		<view class="empty-tip" v-else>
			正在生成回答，请稍候...
		</view>
	</view>
	
	<!-- 检索evidence展示区 -->
	<view class="evidence-container" v-if="ragEvidence && ragEvidence.length > 0">
	
	  <view class="evidence-title">
	    RAG 检索结果
	  </view>
	
	  <view
	    class="evidence-item"
	    v-for="(item, index) in ragEvidence"
	    :key="index"
	  >
	
	    <view class="evidence-score">
	      相似度:
	      {{ item.score ? Number(item.score).toFixed(4) : '0.0000' }}
	    </view>
	
	    <view class="evidence-source">
	      来源:
	      {{ item.source || '未知来源' }}
	    </view>
	
	    <scroll-view
	      scroll-y
	      class="evidence-scroll"
	    >
	      <view class="evidence-text">
	        {{ item.text || '无内容' }}
	      </view>
	    </scroll-view>
	
	  </view>
	
	</view>

</template>

<script setup>
import { ref } from 'vue'
import { onMounted } from 'vue'
const searchText = ref('')
const aiAnswer = ref('') 
const isLoading = ref(false)
const lastQuestion =         ref('')
const ragEvidence = ref([])

const isSpeaking = ref(false)  // 是否正在朗读

// 停止当前朗读（可选）
const stopSpeaking = () => {
  if (window.speechSynthesis) {
    window.speechSynthesis.cancel()
    isSpeaking.value = false
  }
}
const goToKnowledge = () => {
  uni.navigateTo({ url: '/pages/knowledge/knowledge' })
}
// 朗读答案
const speakAnswer = () => {
  if (!aiAnswer.value) return
  if (!window.speechSynthesis) {
    uni.showToast({ title: '当前浏览器不支持语音播报', icon: 'none' })
    return
  }
  // 停止正在播放的（避免重叠）
  if (isSpeaking.value) {
    window.speechSynthesis.cancel()
    isSpeaking.value = false
    // 可以继续播放新的，也可以直接 return，根据需求选择
  }
  const utterance = new SpeechSynthesisUtterance(aiAnswer.value)
  utterance.lang = 'zh-CN'      // 中文
  utterance.rate = 0.9          // 语速 0.1~10，正常1
  utterance.pitch = 1           // 音调
  utterance.onstart = () => { isSpeaking.value = true }
  utterance.onend = () => { isSpeaking.value = false }
  utterance.onerror = () => { isSpeaking.value = false }
  window.speechSynthesis.speak(utterance)
}
const collectAnswer = () => {
  if (!lastQuestion.value || !aiAnswer.value) {
    uni.showToast({ title: '没有可收藏的内容', icon: 'none' })
    return
  }
  const newItem = {
    id: Date.now().toString(36) + Math.random().toString(36).slice(2),
    question: lastQuestion.value,
    answer: aiAnswer.value,
    time: new Date().toLocaleString(),
    category: '其他',
    tags: [],
    notes: ''
  }
  const store = uni.getStorageSync('knowledge_items') || []
  store.unshift(newItem)   // 最新收藏放最前面
  uni.setStorageSync('knowledge_items', store)
  uni.showToast({ title: '已添加到知识库', icon: 'success' })
}

// 跳转到历史页面
const goToHistory = () => {
  uni.navigateTo({
    url: '/pages/history/history'
  })
}
const clearInput = () => {
	searchText.value = ''
}

// 发送按钮点击事件
const handleSend = () => {
  // 校验输入
  if (!searchText.value.trim()) {
    uni.showToast({ title: '请输入内容再发送', icon: 'none' })
    return
  }
lastQuestion.value=searchText.value.trim()
  // 设置加载状态
  isLoading.value = true
  aiAnswer.value = ''

  // ----- 本地服务器配置-----
  const LOCAL_IP = '127.0.0.1'   // 你的电脑IP
  const PORT = '4567'               
  // ---------------------------------------------

// 发起本地请求
uni.request({
  url: `http://${LOCAL_IP}:${PORT}/v1/chat/completions`,
  method: 'POST',
  header: {
    'Content-Type': 'application/json'
  },
  data: {
	message: searchText.value, 
    // 加入RAG参数
    top_k: 3,
    max_tokens: 1024,
    temperature: 0.7,
    top_p: 0.9,

  },
	success: (res) => {
	  console.log('完整返回:', res)
	  
	  if (res.statusCode !== 200) {
		console.error("后端错误:", res.data)
		uni.showToast({ title: '后端报错', icon: 'none' })
		return
	  }

	  if (res.data && res.data.choices && res.data.choices.length > 0) {
		aiAnswer.value = res.data.choices[0].message.content
		
		const newHistory = {
					  question: searchText.value, 
					  answer: aiAnswer.value, 
					  time: new Date().toLocaleString()
					   } 
		const oldHistory = uni.getStorageSync('chat_history') || [] 
		const newHistoryList = [newHistory, ...oldHistory] 
		uni.setStorageSync('chat_history', newHistoryList)

		ragEvidence.value = res.data.evidence || []
		console.log("RAG检索内容:", ragEvidence.value)

		uni.showToast({ title: '回答生成成功', icon: 'success' })
	  } else {
		uni.showToast({ title: '模型未返回内容', icon: 'none' })
	  }
	},
  fail: (err) => {
    console.error('本地请求失败:', err)
    uni.showToast({ title: '连接本地服务器失败，检查IP和防火墙', icon: 'none' })
  },
  complete: () => {
    isLoading.value = false
  }
})
}


const copyAnswer = () =>{
	if(!aiAnswer.value) {
		uni.showToast({
			title:'没有可复制的内容',icon:'none'
		})
		return
	}
	uni.setClipboardData({
		data:aiAnswer.value,
		success:()=>{
			uni.showToast({
				title:'复制成功',icon:'success'
			})
		},
		fail:()=>{
			uni.showToast({
				title:'复制失败,请手动复制',icon:'none'
			})
		}
	})
}

</script>



<style lang="scss" scoped>

.search-container {
	display: flex;
	align-items: center;
	padding: 20rpx;
	gap: 20rpx;
	background-color: #fff;
}
.clear-icon {
	position: absolute;
	right: -20rpx;
	top: 50%;
	transform: translateY(-50%);
	width: 44rpx;
	height: 44rpx;
	line-height: 44rpx;
	text-align: center;
	background-color: #e4e4e4;
	color: #000000;
	border-radius: 50%;
	font-size: 28rpx;
	
	z-index: 10;
}
.search-input-wrapper {
	flex: 1;
	position: relative;
}

.search-input {
	width: 100%;
	padding: 20rpx;
	border: 2rpx solid #e5e5e5;
	border-radius: 40rpx;
	font-size: 26rpx;
	background-color: #f5f5f5;
}

.send-btn {
	width: 130rpx;
	padding: 20rpx 30rpx;
	background-color: #007aff;
	color: #fff;
	border-radius: 20rpx;
	font-size: 26rpx;
	border: none;
	margin-left: 40rpx;
}

.send-btn:disabled {
	background-color: #ccc;
}

.history-btn{
	width:120rpx;
	padding:10rpx 20rpx;
	background-color: #34C759;
	color:#fff;
	border-radius: 15rpx;
	border: none;
	font-size: 24rpx;
	margin-left: 10rpx;
	white-space: nowrap;
}
//答案区样式
.answer-content-wrapper {
  position: relative;
  line-height: 1.6;
}

.answer-text {
  font-size: 28rpx;
  color: #666;
  white-space: pre-line;
}

.collect-plus {
  display: inline-block;
  margin-left: 10rpx;
  font-size: 36rpx;
  color: #007aff;
  font-weight: bold;
  vertical-align: middle;
  padding: 0 8rpx;
  border-radius: 50%;
  background-color: #f0f0f0;
  line-height: 1;
  text-align: center;
  width: 44rpx;
  height: 44rpx;
}
.answer-container {
	background-color: #fff;
	border-radius: 20rpx;
	padding: 30rpx;
	margin-top: 15rpx;
}

.answer-title {
	font-size: 32rpx;
	font-weight: bold;
	color: #333;
	margin-bottom: 20rpx;
}
.action-buttons {
	display: flex;
	gap: 15rpx;
	position: relative;
	top:-75rpx;
	float:right;
	font-size:25rpx;
}
.knowledge-btn{
	display: flex;
	gap: 15rpx;
	position: relative;
	top:-75rpx;
	float:right;
	font-size:25rpx;
	
}
.regenerate-btn, .copy-btn,.voice-btn {
	width: auto;
	padding: 6rpx 28rpx;
	height: 60rpx;
	line-height: 60rpx;
	font-size: 28rpx;
	background-color: #f9f9f9;
	color: #000000;
	border: 1rpx solid #f9f9f9;
	border-radius: 30rpx;
	margin: 0;
}

.regenerate-btn:active, .copy-btn:active {
	background-color: #e9e9e9;
}
.answer-content {
	font-size: 28rpx;
	color: #666;
	line-height: 1.6;
	white-space: pre-line; 
}

.empty-tip {
	font-size: 28rpx;
	color: #999;
	text-align: center;
	padding: 40rpx 0;
}

// rag检索的evidence样式
.evidence-container {
  margin-top: 20rpx;
  padding: 20rpx;
  background: #f5f5f5;
  border-radius: 16rpx;

  display: flex;
  flex-direction: column;
}

.evidence-item {
  margin-bottom: 20rpx;
  padding: 20rpx;
  background: white;
  border-radius: 12rpx;
}

.evidence-score {
  color: #007aff;
  font-weight: bold;
  margin-bottom: 10rpx;
}

.evidence-source {
  color: #666;
  font-size: 24rpx;
  margin-bottom: 10rpx;
}

.evidence-scroll {
  max-height: 300rpx;
}

.evidence-text {
  color: #333;
  line-height: 1.6;
  word-break: break-all;
}

</style>