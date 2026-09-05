<template>
	<view class="home">
		<!--轮播图片-->
		<view>
			<swiper indicator-dots indicator-color="rgba(255,255,255,0.3)" indicator-active-color=#ffffff circular
				autoplay interval="2000">
				<swiper-item>
					<image src="../../static/images/pic1.webp" class="pic1" mode="aspectFill"></image>
				</swiper-item>
				<swiper-item>
					<image src="../../static/images/pic2.webp" class="pic1" mode="aspectFill"></image>
				</swiper-item>
			</swiper>
		</view>
		<!--功能标签-->
		<view class="wrap">
			
			<view class="dev-area">

				<view class="dev-cart">
					<view class="dev-box">
						<navigator  url="/pages/environment/environment">异常信息提示</navigator>
						<image class="dev-logo" src="../../static/logo/error_icon.png" mode=""></image>
					</view>
				</view>
				<view class="dev-cart">
					<view class="dev-box">
						<navigator url="/pages/data_pages/data_pages">环境信息记录</navigator>
						<image class="dev-logo" src="../../static/logo/message_icon.png" mode=""></image>
					</view>
				</view>

			</view>
			
		</view>
		<view class="txt_label">
			<text>异常数据总览</text>
			
		</view>
		<view class="label_Style">
			<echarts :option="option1" style="height: 300px;" ></echarts>
		</view>
<!-- 		<view class="label_Style">
			<echarts :option="option2" style="height: 300px;" ></echarts>
		</view> -->


	</view>


</template>

<script> 
import echarts from '@/components/echarts/echarts.vue'
	export default {
		data() {
			return {
				Style1: {
					  tooltip: {
						trigger: 'item'
					  },
					  legend: {
						top: '5%',
						left: 'center'
					  },
					  
					  series: [
						{
						  name: 'Access From',
						  type: 'pie',
						  radius: ['40%', '70%'],
						  avoidLabelOverlap: false,
						  itemStyle: {
							borderRadius: 10,
							borderColor: '#fff',
							borderWidth: 2
						  },
						  label: {
							show: false,
							position: 'center'
						  },
						  emphasis: {
							label: {
							  show: true,
							  fontSize: 40,
							  fontWeight: 'bold'
							}
						  },
						  labelLine: {
							show: false
						  },
						  data: [
							{ value: 3, name: '水位' },
							{ value: 5, name: '土壤PH' },
							{ value: 2, name: '温度' },
							{ value: 4, name: '湿度' },
							{ value: 2, name: '光照' }
						  ]
						}
					  ]
					},
					Style2:	{
						  title: {
						    text: 'Referer of a Website',
						    subtext: 'Fake Data',
						    left: 'center'
						  },
						  tooltip: {
						    trigger: 'item'
						  },
						  legend: {
						    orient: 'vertical',
						    left: 'left'
						  },
						  series: [
						    {
						      name: 'Access From',
						      type: 'pie',
						      radius: '50%',
						      data: [
						        { value: 1048, name: 'Search Engine' },
						        { value: 735, name: 'Direct' },
						        { value: 580, name: 'Email' },
						        { value: 484, name: 'Union Ads' },
						        { value: 300, name: 'Video Ads' }
						      ],
						      emphasis: {
						        itemStyle: {
						          shadowBlur: 10,
						          shadowOffsetX: 0,
						          shadowColor: 'rgba(0, 0, 0, 0.5)'
						        }
						      }
						    }
						  ]
					}
			}
		},
		components: {
			echarts
		},
		onLoad() {
			this.option1 = this.Style1;
			this.option2 = this.Style2;
		},
		methods: {
			
		},
		onShow() {

		},
		methods: {

			
		}
	}

</script>

<style lang="scss" scoped>
	.home{
		background:
		linear-gradient(to bottom,transparent,#fff 100%),
		linear-gradient(to right,#beecd8 20%,#F4E2D8);
		
	}
	.wrap {
		padding: 30rpx;
	}
	.dev-area {
		display: flex;
		justify-content: space-between;
	}
	.dev-cart {
		height: 150rpx;
		width: 320rpx;
		border-radius: 30rpx;
		margin-top: 30rpx;
		display: flex;
		flex-direction: row;	
		justify-content: space-between;
		align-items: center;
		box-shadow: 0 0 15rpx #ccc;
		// background:
		// 	 linear-gradient(to bottom,transparent,#fff 100%),
		// 	linear-gradient(to right,#A6DADF 20%,#C4F0C5);
			
		background: linear-gradient(to top, #c1dfc4 0%, #deecdd 100%);	
	}
	.dev-box{
		display: flex;
		flex-direction: row;
		align-items: center;
		font-size: 40rpx;
		text-align: center;
		color: #6d6d6d;

	}
	.dev-logo {
		width: 60rpx;
		height: 60rpx;
		margin-top: 0rpx;
		
	}
	swiper {
		width: 100vw;
		height: 400rpx;
		border: 1rpx solid green;

		swiper_item {

			background-color: #6d6d6d;
		}
	}
	.pic1 {
		width: 100%;
		height: 100%;
	}

	.pic2 {
		width: 100%;
		height: 100%;
	}
	.txt_label{
		width: 100%;
		height: 60rpx;
		box-shadow: 0 0 15rpx #eee;
		font-size: 40rpx;
	}
	.label_Style{
		padding-top: 50rpx;
		margin-top: 30rpx;

	}
</style>