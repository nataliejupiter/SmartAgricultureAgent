<template>
	<view class="Row_blank">
		<view class="top_bar">异常信息</view>
		<view class="secton">	
			<view class="Row">
				<view class="left">
					<uni-icons type="link" size="30" color="#28b389"></uni-icons>
					<view class="txt">设备ID</view>
				</view>
				<view class="right">
					ZLNT_20250105_002<uni-icons type="right" size="20"></uni-icons>
				</view>
				<button class="Button" @click="open_doc">打开弹窗</button>
			</view>
			
			<view class="Row_blank"></view>
			
			<view class="Row">
				<view class="left">
					<uni-icons type="info" size="30" color="red"></uni-icons>
					<view class="txt">预警类型</view>
				</view>
				<view class="right">
					水位<uni-icons type="right" size="20"></uni-icons>
				</view>
				<button class="Button" @click="open_doc">打开弹窗</button>
			</view>
			
			
			<view class="Row">
				<view class="left">
					<uni-icons type="link" size="30" color="#28b389"></uni-icons>
					<view class="txt">设备名称</view>
				</view>
				<view class="right">
					<uni-icons type="right" size="20"></uni-icons>
				</view>
				<button class="Button" @click="open_doc">检测数值</button>
			</view>
			
			
			<view class="Row">
				<view class="left">
<!-- 					<uni-icons type="list" size="30" color="#28b389"></uni-icons> -->
					<view class="txt">检测数值</view>
				</view>
				<view class="right">
					20.1
				</view>
				<button class="Button" @click="open_doc">检测数值</button>
			</view>
			
			<view class="Row">
				<view class="left">
<!-- 					<uni-icons type="list" size="30" color="#28b389"></uni-icons> -->
					<view class="txt">最大值</view>
				</view>
				<view class="right">
					50
				</view>
				<button class="Button" @click="open_doc">检测数值</button>
			</view>
			
			<view class="Row">
				<view class="left">
<!-- 					<uni-icons type="list" size="30" color="#28b389"></uni-icons> -->
					<view class="txt">最小值</view>
				</view>
				<view class="right">
					30
				</view>
				<button class="Button" @click="open_doc">检测数值</button>
			</view>
			
			<view class="Row">
				<view class="left">
<!-- 					<uni-icons type="list" size="30" color="#28b389"></uni-icons> -->
					<view class="txt">告警时间</view>
				</view>
				<view class="right">
					2025-01-05-13:51:12
				</view>
				<button class="Button" @click="open_doc">检测数值</button>
			</view>
			
			<view class="Row">
				<view class="left">
<!-- 					<uni-icons type="list" size="30" color="#28b389"></uni-icons> -->
					<view class="txt">检测数值</view>
				</view>
				<view class="right">
					20.1
				</view>
				<button class="Button" @click="open_doc">检测数值</button>
			</view>
			
			<view class="Row_blank"></view>
			
			<view class="Row">
				<view class="left">
<!-- 					<uni-icons type="list" size="30" color="#28b389"></uni-icons> -->
					<view class="txt">告警名称</view>
				</view>
				<view class="right">
					水位预警
				</view>
				<button class="Button" @click="open_doc">检测数值</button>
			</view>

			<view class="Row">
				<view class="left">
<!-- 					<uni-icons type="list" size="30" color="#28b389"></uni-icons> -->
					<view class="txt">告警信息</view>
				</view>
				<view class="right_txt">
					水位预警，标准水位高度在30-50，实测数值为2.1，低于水位设定的最低值，请及时处理。
				</view>
				<button class="Button" @click="open_doc">检测数值</button>
			</view>
			
		</view>
		
		
	</view>
</template>

<script>
	export default {
		data() {
			return {
				
			}
		},
		methods: {
			
		}
	}
</script>

<style lang="scss" scoped>
	.top_bar{
		height: 75rpx;
		display: flex;
		font-size:40rpx;
		justify-content: center;
		align-items: center;
		background-color: #19A6F245;
		color: #000;
	}
	.Row_blank{
		height: 50rpx;
		background-color: #FAF5FD;
		
	}
	.secton {
		
		//margin: 50rpx auto;FFF
		border: 1rpx solid #FFF;
		border-radius: 10rpx;
		box-shadow: 0 0 30rpx rgba(0, 0, 0, 0.05);
	}

	.Row {
		display: flex;
		justify-content: space-between;
		padding: 0 30rpx;
		height: 100rpx;
		border: 1rpx solid #eee;
		background-color: #fff;
		position: relative;
	}

	.left {
		display: flex;
		align-items: center;
	}

	.right {
		
		display: flex;
		align-items: center;
		font-size: 35rpx;
		
		white-space: nowrap; 
		text-overflow:ellipsis; 
		overflow:hidden; 
	

	}
	.right_txt{
		width:400rpx;
		display: flex;
		align-items: center;
		font-size: 35rpx;
		
		white-space: nowrap; 
		text-overflow:ellipsis; 
		overflow:hidden;		
		
	}
	.Button {
		position: absolute;
		top: 0;
		left: 0;
		height: 100rpx;
		width: 100%;
		opacity: 0;
	}

	.txt {
		padding: 20rpx;
		color: #666;
	}

</style>
