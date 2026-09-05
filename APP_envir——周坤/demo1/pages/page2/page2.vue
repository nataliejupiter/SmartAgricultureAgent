<template>
	<view class="AI_layout">
		<view>
			<text class="kala_text" space="ensp">{{ text1 }}</text>			
		</view>
		<view>
			<text class="kala_text" space="ensp">{{ text2 }}</text>
		</view>
		<view>
			<text class="kala_text" space="ensp">{{ text3 }}</text>
		</view>
		<view>
			<text class="kala_text" space="ensp">{{ text4 }}</text>
		</view>
		<view>
			<text class="kala_text" space="ensp">{{ text5 }}</text>
		</view>
		<view>
			<text class="kala_text" space="ensp">{{ text6 }}</text>
		</view>
		<view>
			<text class="kala_text" space="ensp">{{ text7 }}</text>
		</view>
		<view>
			<text class="kala_text" space="ensp">{{ text8 }}</text>
		</view>
		<view>
			<text class="kala_text" space="ensp">{{ text9 }}</text>
		</view>
		<view>
			<text class="kala_text" space="ensp">{{ text10 }}</text>
		</view>
	</view>

</template>

<script>
	export default{
		data() {
		  return {
		    text1:'         ',
		    text2:'     来自江西理工大学的智理农田团队',
		    text3:'',
		    text4:'',
		    text5:'',
		    text6:'',
		    text7:'',
		    text8:'',
		    text9:'',
		    text10:'',
		  }
		}
	}

</script>

<style lang="scss" scoped>
	.AI_layout{
		width: 100%;
		height: 400rpx;
		background:

			linear-gradient(to bottom, transparent, #fff 600rpx),
			linear-gradient(to right, #beecd8 20%, #F4E2D8);
			
		min-height: 100vh;
	}
	.kala_text{
		font-size: 40rpx;
		
		
	}


</style>