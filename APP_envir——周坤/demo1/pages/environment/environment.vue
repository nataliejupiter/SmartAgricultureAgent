<template>
	<view class="main">
		<view>
			<uni-search-bar @confirm="search" :focus="true" v-model="searchValue" @blur="blur" @input="input"
				@cancel="cancel" @change="change" @clear="clear">
			</uni-search-bar>
			历史记录：{{ searchValue }}
		</view>
		<view class="message_bar">
			<view class="txt">设备ID：ZLNT_20250108_001</view>
			<view class="txt">异常类型：温度</view>
			<view class="txt">位置：</view>
			<navigator url='/warning_pages/warning_pages'>告警时间：2025-03-06 21:41:09 详情</navigator>
		</view>
		<view class="message_bar">
			<view class="txt">设备ID：ZLNT_20250108_002</view>
			<view class="txt">异常类型：水位</view>
			<view class="txt">位置：</view>
			<navigator>告警时间：2025-03-05 14:31:11 详情</navigator>
		</view>
		<view class="message_bar">
			<view class="txt">设备ID：ZLNT_20250108_003</view>
			<view class="txt">异常类型：水位</view>
			<view class="txt">位置：</view>
			<navigator>告警时间：2025-03-04 11:23:23 详情</navigator>

		</view>

		<view class="message_bar">
			<view class="txt">设备ID：ZLNT_20250108_004</view>
			<view class="txt">异常类型：光照</view>
			<view class="txt">位置：</view>
			<navigator>告警时间：2025-03-04 22:33:41 详情</navigator>
		</view>

		<view class="message_bar">
			<view class="txt">设备ID：ZLNT_20250108_004</view>
			<view class="txt">异常类型：光照</view>
			<view class="txt">位置：</view>
			<navigator>告警时间：2025-03-04 22:33:56 详情</navigator>
		</view>

		<view class="message_bar">
			<view class="txt">设备ID：ZLNT_20250108_004</view>
			<view class="txt">异常类型：光照</view>
			<view class="txt">位置：</view>
			<navigator>告警时间：2025-03-04 22:33:44 详情</navigator>
		</view>

		<view class="message_bar">
			<view class="txt">设备ID：ZLNT_20250108_004</view>
			<view class="txt">异常类型：光照</view>
			<view class="txt">位置：</view>
			<navigator>告警时间：2025-03-04 22:33:31 详情</navigator>
		</view>
		<button @click="initSocket">更新信息</button>
	</view>
</template>

<script>
	export default {
		data() {
			return {
				searchValue: '123123',
				time: '',
				socket: null,
				serverUrl: "ws://123.60.15.215:25565" // 或 wss://（加密协议）

			}
		},
		methods: {
			search(res) {
				uni.showToast({
					title: '搜索：' + res.value,
					icon: 'none'
				})
			},
			input(res) {
				console.log('----input:', res)
			},
			clear(res) {
				uni.showToast({
					title: 'clear事件，输入值为：' + res.value,
					icon: 'none'
				})
			},
			blur(res) {
				uni.showToast({
					title: 'blur事件，输入值为：' + res.value,
					icon: 'none'
				})
			},
			cancel(res) {
				uni.showToast({
					title: '点击取消，输入值为：' + res.value,
					icon: 'none'
				})
			},

			getNowTime() {
				var date = new Date();
				//年 getFullYear()：四位数字返回年份
				var year = date.getFullYear(); //getFullYear()代替getYear()
				//月 getMonth()：0 ~ 11
				var month = date.getMonth() + 1;
				//日 getDate()：(1 ~ 31)
				var day = date.getDate();
				//时 getHours()：(0 ~ 23)
				var hour = date.getHours();
				//分 getMinutes()： (0 ~ 59)
				var minute = date.getMinutes();
				//秒 getSeconds()：(0 ~ 59)
				var second = date.getSeconds();
				var time = year + '-' + this.addZero(month) + '-' + this.addZero(day) + ' ' + this.addZero(hour) +
					":" + this.addZero(minute) + ':' + this.addZero(second);
				this.time = time
			},
			//小于10的拼接上0字符串
			addZero(s) {
				return s < 10 ? ('0' + s) : s;
			}



		}

	}
</script>
<style lang="scss" scoped>
	.main {
		background:
			linear-gradient(to top, transparent, #fff 400rpx),
			linear-gradient(to left, #beecd8 20%, #F4E2D8);

		min-height: 80vh;

	}

	.message_bar {
		font-size: 40rpx;
		border: 1rpx solid #eee;
	}

	.txt {
		margin-top: 15rpx;
		margin-bottom: 15rpx;
	}
</style>