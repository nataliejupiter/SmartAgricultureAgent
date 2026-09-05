<template>

	<view class="item">
		{{item.dat}}
	</view>
</template>

<script>
	export default {
		name: "UserItem",
		props:{
			item:{
				type:Object,
				default(){
					return {
						data:'668'
					}
				}
					
			}
			
		},
		data() {
			return {

			};
		}
	}
</script>

<style lang="scss">
	.item {
		display: inline-block;
		background: #eaeaea;
		padding: 20rpx 50rpx;
		border-radius: 50rpx;
		font-size: 40rpx;
		margin-right: 10rpx;
	}
</style>