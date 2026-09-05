<template>
	<view>
		<view>
<!-- 		<text class="txt_style">湿度-时间</text> -->
		<echarts :option="Show1_option" style="height: 280px;" @click="echartsClick"></echarts>
		</view>
		<view>
<!-- 		<text class="txt_style">湿度-时间</text> -->
		<echarts :option="Show2_option" style="height: 280px;" @click="echartsClick"></echarts>
		</view>		
		<view>
<!-- 		<text class="txt_style">湿度-时间</text> -->
		<echarts :option="Show3_option" style="height: 280px;" @click="echartsClick"></echarts>
		</view>			
		
		<button class="botton_style" size="mini" @click="updateClick">切换数据</button>
	</view>
</template>

<script>
	import echarts from '@/components/echarts/echarts.vue'
	export default {
		data() {
			return {
				//Show_option: {},
				Show1_option: {},
				Show2_option: {},
				Show3_option: {},
				//折线图1——温度————时间
				option2: {
					title: {
						text: '温度-时间',
						left: 'center'
					},
					notMerge: true, // 自定义变量：true代表不合并数据，比如从折线图变为柱形图则需设置为true；false或不写代表合并
					tooltip: {
						trigger: 'axis',
						positionStatus: true,
						formatterStatus: false, // 自定义变量：是否格式化tooltip，设置为false时下面三项均不起作用
						formatterUnit: '元', // 自定义变量：数值后面的单位
						formatFloat2: true, // 自定义变量：是否格式化为两位小数
						formatThousands: true // 自定义变量：是否添加千分位
					},
					legend: {
						data: ['', '']
					},
					grid: {
						left: '8%',
						right: '8%',
						bottom: '8%',
						containLabel: true
					},
					xAxis: [{
						name: '时间（h）',
						nameLocation: 'middle', //轴位置
						nameGap: 26, //name名字与轴线间距
						type: 'value',
						axisLine: {
							onZero: false
						}
					}],
					yAxis: [{
						name: '温度（°C）',
						nameGap: 26, //name名字与轴线间距
						type: 'value',
						axisLine: {
							onZero: false
						},
					  axisLabel: {
						formatter: '{value} °C'
					  }
					}],
					series: [{
						id: 'a',
						type: 'line',
						smooth: true,
						symbolSize: 0,
						data: [
							[0, 24.15],
							[1.18, 24.01],
							[1.3, 24.67],
							[2.46, 24.99],
							[2.66, 25.02],
							[3.88, 25.53],
							[4.12, 26.09],
							[4.32, 26.09],
							[5.52, 26.59],
							[5.62, 26.69],
							[6.52, 27.79],
							[6.72, 28.09],
							[7.32, 28.19],
							[7.62, 28.79],
							[8.22, 29.09],
							[8.52, 30.79],
						]
					}]
				},
				//折线图2——湿度————时间
				option3: {
					title: {
						text: '湿度-时间',
						left: 'center'
					},
					notMerge: true, // 自定义变量：true代表不合并数据，比如从折线图变为柱形图则需设置为true；false或不写代表合并
					tooltip: {
						trigger: 'axis',
						positionStatus: true,
						formatterStatus: false, // 自定义变量：是否格式化tooltip，设置为false时下面三项均不起作用
						formatterUnit: '元', // 自定义变量：数值后面的单位
						formatFloat2: true, // 自定义变量：是否格式化为两位小数
						formatThousands: true // 自定义变量：是否添加千分位
					},
					legend: {
						data: ['', '']
					},
					grid: {
						left: '8%',
						right: '8%',
						bottom: '8%',
						containLabel: true
					},
					xAxis: [{
						name: '时间（h）',
						nameLocation: 'middle', //轴位置
						nameGap: 26, //name名字与轴线间距
						type: 'value',
						axisLine: {
							onZero: false
						}
					}],
					yAxis: [{
						name: '温度（%）',
						nameGap: 26, //name名字与轴线间距
						type: 'value',
						axisLine: {
							onZero: false
						},
					  axisLabel: {
						formatter: '{value} %'
					  }
					}],
					series: [{
						id: 'a',
						type: 'line',
						smooth: true,
						symbolSize: 0,
						data: [
							[0, 54.15],
							[0.02, 56.02],
							[0.08, 58.1],
							[0.18, 60.01],
							[0.3, 61.67],
							[0.46, 62.99],
							[0.66, 63.92],
							[0.88, 64.53],
							[1.12, 64.99],
							[1.42, 65.39],
							[1.72, 65.85],
							[2.06, 66.39],
							[2.42, 66.99],
							[2.82, 67.63],
							[3.24, 68.28],
							[3.68, 68.94],
							[4.14, 69.62],
							[4.64, 70.33],
							[5.14, 71.1],
							[5.68, 71.93],
							[6.22, 72.82],
							[6.8, 72.74],
							[7.38, 74.65],
							[8, 75.35],
							[8.62, 75.75],
							[9.26, 75.8],
							[9.9, 75.56],
							[10.58, 75.19],
							[11.26, 74.8],
							[11.94, 74.52],
							[12.64, 74.31],
							[13.34, 74.26],
							[14.04, 74.36],
							[14.76, 74.51],
							[15.46, 74.71],
							[16.2, 74.84],
							[16.92, 74.92],
							[17.64, 74.85],
							[18.38, 74.69],
							[19.1, 74.46],
							[19.84, 74.21],
							[20.56, 74.06],
							[21.28, 73.99],
							[22, 74.03],
							[22.72, 74.14],
							[23.46, 74.27],
							[24.16, 74.36],
							[24.88, 74.38],
							[25.58, 74.31],
							[26.28, 74.2],
							[26.98, 74.07],
							[27.68, 73.97],
							[28.36, 73.91],
							[29.04, 73.89],
							[29.72, 73.94],
							[30.38, 74.02],
							[31.04, 74.13],
							[31.68, 74.22],
							[32.34, 74.26],
							[32.98, 74.28],
							[33.6, 74.26],
							[34.22, 74.24],
							[34.84, 74.19],
							[35.44, 74.19],
							[36.04, 74.18],
							[36.64, 74.18],
							[37.2, 74.24],
							[37.78, 74.26],
							[38.34, 74.32],
							[38.9, 74.36],
							[39.44, 74.39],
							[39.98, 74.42],
							[40.5, 74.43],
							[41.02, 74.46],
							[41.52, 74.47],
							[42.02, 74.48],
							[42.52, 74.49],
							[42.98, 74.5],
							[43.46, 74.5],
							[43.92, 74.49],
							[44.36, 74.46],
							[44.8, 74.46],
							[45.22, 74.46],
							[45.62, 74.49],
							[46.02, 74.51],
							[46.4, 74.51],
							[46.78, 74.51],
							[47.14, 74.51],
							[47.48, 74.52],
							[47.82, 74.54],
							[48.14, 74.55],
							[48.44, 74.56],
							[48.72, 74.58],
							[48.98, 74.6],
							[49.24, 74.63],
							[49.46, 74.64],
							[49.68, 74.63],
							[49.86, 74.59],
							[50.02, 74.52],
							[50.18, 74.42],
							[50.3, 74.28],
							[50.4, 74.08],
							[50.48, 73.76]
						]
					}]
				},				
				//折线图3——灌溉水位————时间
				option4: {
					title: {
						text: '灌溉水位-时间',
						left: 'center'
					},
					notMerge: true, // 自定义变量：true代表不合并数据，比如从折线图变为柱形图则需设置为true；false或不写代表合并
					tooltip: {
						trigger: 'axis',
						positionStatus: true,
						formatterStatus: false, // 自定义变量：是否格式化tooltip，设置为false时下面三项均不起作用
						formatterUnit: '元', // 自定义变量：数值后面的单位
						formatFloat2: true, // 自定义变量：是否格式化为两位小数
						formatThousands: true // 自定义变量：是否添加千分位
					},
					legend: {
						data: ['', '']
					},
					grid: {
						left: '8%',
						right: '8%',
						bottom: '8%',
						containLabel: true
					},
					xAxis: [{
						name: '时间（h）',
						nameLocation: 'middle', //轴位置
						nameGap: 26, //name名字与轴线间距
						type: 'value',
						axisLine: {
							onZero: false
						}
					}],
					yAxis: [{
						name: '高度（cm）',
						nameGap: 26, //name名字与轴线间距
						type: 'value',
						axisLine: {
							onZero: false
						},
					  axisLabel: {
						formatter: '{value} cm'
					  }
					}],
					series: [{
						id: 'a',
						type: 'line',
						smooth: true,
						symbolSize: 0,
						data: [
							[0, 14.15],
							[1.18, 14.01],
							[1.3, 14.27],
							[2.46, 8.29],
							[2.66, 8.02],
							[3.88, 14.13],
							[4.12, 14.09],
							[4.32, 14.09],
							[5.52, 7.59],
							[5.62, 7.69],
							[6.52, 7.79],
							[6.72, 14.09],
							[7.32, 14.19],
							[7.62, 14.49],
							[8.22, 7.09],
							[8.52, 7.49],
						]
					}]
				},				
				//柱状图1——温度————时间
				option5: {
					title: {
						text: '温度-时间',
						left: 'center'
					},
					notMerge: true, // 自定义变量：true代表不合并数据，比如从折线图变为柱形图则需设置为true；false或不写代表合并
					xAxis: {
						type: 'category',
						data: ['Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat', 'Sun']
					},
					yAxis: {
						type: 'value'
					},
					series: [{
						data: [26, 30, 28, 30, 29.5, 28.8, 27.6],
						type: 'bar',
						showBackground: true,
						backgroundStyle: {
							color: 'rgba(220, 220, 220, 0.8)'
						}
					}]
				},
				option6: {
					title: {
						text: '湿度-时间',
						left: 'center'
					},
					notMerge: true, // 自定义变量：true代表不合并数据，比如从折线图变为柱形图则需设置为true；false或不写代表合并
					xAxis: {
						type: 'category',
						data: ['Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat', 'Sun']
					},
					yAxis: {
						type: 'value'
					},
					series: [{
						data: [49, 38, 43, 54, 50, 47, 56],
						type: 'bar',
						showBackground: true,
						backgroundStyle: {
							color: 'rgba(220, 220, 220, 0.8)'
						}
					}]
				},
				option7: {
					title: {
						text: '灌溉水位-时间',
						left: 'center'
					},
					notMerge: true, // 自定义变量：true代表不合并数据，比如从折线图变为柱形图则需设置为true；false或不写代表合并
					xAxis: {
						type: 'category',
						data: ['Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat', 'Sun']
					},
					yAxis: {
						type: 'value'
					},
					series: [{
						data: [150, 167, 157, 160, 163, 155, 159],
						type: 'bar',
						showBackground: true,
						backgroundStyle: {
							color: 'rgba(220, 220, 220, 0.8)'
						}
					}]
				},
				

			};
		},
		components: {
			echarts
		},
		onLoad() {
			this.Show1_option = this.option2;//温度
			this.Show2_option = this.option3;//湿度
			this.Show3_option = this.option4;//灌溉水位
		},
		methods: {
			/**
			 * 点击事件
			 * @param {Object} params
			 */
			echartsClick(params) {
				console.log('点击数据', params)
			},
			/**
			 * 切换数据
			 */
			updateClick() {
				if (this.Show1_option === this.option2) {
					this.Show1_option = this.option5;
					this.Show2_option = this.option6;
					this.Show3_option = this.option7;
					
				} else {
					this.Show1_option = this.option2;
					this.Show2_option = this.option3;
					this.Show3_option = this.option4;	
				}
			}
		}
	};
</script>

<style lang="scss">
	.botton_style{
		border-radius: 10rpx;
		display: flex;
		flex-direction: column;
		justify-content: center;
		align-items: center;
		margin-bottom: 10rpx;
		
	}
	// .txt_style{
	// 	width: 100%;
	// 	height: 70rpx;
	// 	font-size: 40rpx;
	// 	display: flex;
	// 	flex-direction: column;
	// 	justify-content: center;
	// 	align-items: center;
	// 	margin-bottom: 10rpx;
	// }
	
</style>
