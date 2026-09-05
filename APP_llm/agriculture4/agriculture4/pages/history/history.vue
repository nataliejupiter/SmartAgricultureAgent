<template>
	<view class="history-page">
		<view class="header">
			<button @click="goBack" class="back-btn">← 返回</button>
			<text class="title">历史对话</text>
		</view>

		<view class="history-list">
			<view class="item" v-for="(item, index) in historyList" :key="index">
				<view class="question">Q：{{ item.question }}</view>
				<view class="answer">A：{{ item.answer }}</view>
				<view class="time">{{ item.time }}</view>
			</view>
			<view class="empty-tip" v-if="historyList.length === 0">
				暂无历史记录
			</view>
		</view>

		<button type="warn" @click="clearHistory" class="clear-btn">
			清空全部历史
		</button>
	</view>
</template>

<script setup>
import { ref} from 'vue'
import {onLoad} from '@dcloudio/uni-app'

const historyList = ref([])

onLoad(() => {
  const history = uni.getStorageSync('chat_history') || []
  historyList.value = history
})

const goBack = () => {
  uni.navigateBack()
}

const clearHistory = () => {
  uni.showModal({
    title: '提示',
    content: '确定要清空所有历史记录吗？',
    success: (res) => {
      if (res.confirm) {
        historyList.value = []
        uni.setStorageSync('chat_history', [])
        uni.showToast({ title: '已清空' })
      }
    }
  })
}
</script>

<style lang="scss" scoped>
.history-page {
	padding: 20rpx;
	min-height: 100vh;
	background-color: #f5f5f5;
}

.header {
	display: flex;
	align-items: center;
	justify-content: center;
	position: relative; 
	margin-bottom: 30rpx;
	background-color: #fff;
	padding: 20rpx;
	border-radius: 20rpx;
	width: 100%;
}


.back-btn {
	position: absolute; 
	left: 20rpx;
	top: 50%;
	transform: translateY(-50%);
	background-color: #007aff;
	color: #fff;
	border: none;
	border-radius: 10rpx;
	padding: 10rpx 20rpx;
	font-size: 26rpx;
}

.title {
	font-size: 36rpx;
	font-weight: bold;
	text-align: center;
}

.history-list {
	background-color: #fff;
	border-radius: 20rpx;
	padding: 20rpx;
	margin-bottom: 40rpx;
}

.item {
	padding: 20rpx 0;
	border-bottom: 1rpx solid #eee;
}

.question {
	color: #333;
	font-weight: 500;
	margin-bottom: 10rpx;
	font-size: 28rpx;
}

.answer {
	color: #666;
	line-height: 1.5;
	margin-bottom: 10rpx;
	font-size: 26rpx;
}

.time {
	color: #999;
	font-size: 24rpx;
}

.empty-tip {
	text-align: center;
	padding: 40rpx 0;
	color: #999;
	font-size: 28rpx;
}

.clear-btn {
	width: 100%;
	background-color: #ff3b30;
	color: #fff;
	border: none;
	border-radius: 20rpx;
	padding: 25rpx;
	font-size: 28rpx;
}
</style>