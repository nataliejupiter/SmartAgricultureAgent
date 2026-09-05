<template>
	<view class="User_layput">
		<!--		页面logo			-->
		
		<view class="UserInfo">
			<view class="Team_logo">
				<image class="logo" src="../../static/team_logo.png" mode="aspectFill"></image>
			</view>
			<view class="nickname">"智"理农田</view>
		</view>
		<!--		页面logo			-->
		<!--		用户菜单列表			-->
		<view class="secton">
			<view class="list">
				<view class="Row">
					<view class="left">
						<uni-icons type="folder-add-filled" size="30" color="#28b389"></uni-icons>
						<view class="txt">使用文档</view>
					</view>
					<view class="right">
						<uni-icons type="right" size="20"></uni-icons>
					</view>
					<navigator class="Button" url="/pages/User_doc/User_doc">打开弹窗</navigator>
				</view>

				<view class="Row">
					<view class="left">
						<uni-icons type="email-filled" size="30" color="#28b389"></uni-icons>
						<view class="txt">联系我们</view>
					</view>
					<view class="right">
						<uni-icons type="right" size="20"></uni-icons>
					</view>
					<button class="Button" @click="open">打开弹窗</button>
				</view>
				<!---->
<!-- 				<view class="Row">
					<view class="left">
						<uni-icons type="flag-filled" size="30" color="#28b389"></uni-icons>
						<view class="txt">帮助</view>
					</view>
					<view class="right">
						<uni-icons type="right" size="20"></uni-icons>
					</view>
					<navigator url = "/pages/help_doc/help_doc" class = "Button">团队介绍</navigator>
				</view> -->
				<!--	-->
				<view class="Row">
					<view class="left">
						<uni-icons type="person-filled" size="30" color="#28b389"></uni-icons>
						<view class="txt">团队介绍</view>
						

					</view>
					<view class="right">
						<uni-icons type="right" size="20"></uni-icons>
					</view>
					<navigator url = "/pages/page2/page2" class = "Button">团队介绍</navigator>
				</view>
			</view>

		</view>
		<view class="secton">
			<view class="list">
				<!--	-->
				<view class="Row">
					<view class="left">
						<uni-icons type="notification-filled" size="30" color="#28b389"></uni-icons>
						<view class="txt">订阅更新</view>
						
					</view>
					<view class="right">
						<uni-icons type="right" size="20"></uni-icons>
					</view>
					<button class="Button" @click="open_update">打开弹窗</button>
				</view>
				<!--	-->
				<view class="Row">
					<view class="left">
						<uni-icons type="help-filled" size="30" color="#28b389"></uni-icons>
						<view class="txt">常见问题</view>
					</view>
					<view class="right">
						<uni-icons type="right" size="20"></uni-icons>
					</view>
					<navigator url = "/pages/help_doc/help_doc" class = "Button">团队介绍</navigator>
				</view>

			</view>

		</view>
		<!--		用户菜单列表			-->
		<!--		弹出层			-->
		<uni-popup ref="popup" type="center" :animation="false">

			<view class="info_popup">
				<view class="popup_Header">
					<view></view>
					<view class="popup_title">联系信息</view>
					<view class="close_popup" @click="Close_popup">
						<uni-icons type="closeempty" size="20" color="#999"></uni-icons>
					</view>
				</view>
				<text selectable class="popup_txt">email:926374287@qq.com</text>
			</view>
		</uni-popup>
		
		<uni-popup ref="Team_popup" type="center" :animation="false">
		
			<view class="info_popup">
				<view class="popup_Header">
					<view></view>
					<view class="popup_title">联系信息</view>
					<view class="close_popup" @click="Close_Team_popup">
						<uni-icons type="closeempty" size="20" color="#999"></uni-icons>
					</view>
				</view>
				<text selectable class="popup_txt">email:926374287@qq.com</text>
			</view>
		</uni-popup>
		
		<uni-popup ref="Update_popup" type="center" :animation="false">
		
			<view class="info_popup">
				<view class="popup_Header">
					<view></view>
					<view class="popup_title">暂无更新</view>
					<view class="close_popup" @click="Close_Update_popup">
						<uni-icons type="closeempty" size="20" color="#999"></uni-icons>
					</view>
				</view>

			</view>
		</uni-popup>

		<uni-popup ref="docx" type="center" :animation="false">
		
			<view class="info_popup">
				<view class="popup_Header">
					<view></view>
					<view class="popup_title">暂无更新</view>
					<view class="close_popup" @click="Close_docx_popup">
						<uni-icons type="closeempty" size="20" color="#999"></uni-icons>
					</view>
				</view>
				<scroll-view scroll-y>
					<view class="content"></view>
				</scroll-view>
			</view>
		</uni-popup>

		
		
		
		
	</view>

</template>

<script>
	export default {
		methods: {
			open() {
				// 通过组件定义的ref调用uni-popup方法 ,如果传入参数 ，type 属性将失效 ，仅支持 ['top','left','bottom','right','center']
				this.$refs.popup.open('center')
			},
			Close_popup() {
				this.$refs.popup.close()
			},
			// Close_Team_popup() {
			// 	this.$refs.Team_popup.close()
			// },
			// open_team(){
			// 	this.$refs.Team_popup.open('buttom')
			// }, 
			Close_Update_popup() {
				this.$refs.Update_popup.close()
			},
			open_update(){
				this.$refs.Update_popup.open('buttom')
			},
			Close_docx_popup() {
				this.$refs.docx.close()
			},
			open_doc(){
				this.$refs.docx.open('buttom')
			}
			// Open_file(res){
			// 	uni.openDocument({
			// 		filePath:"file:///E:/51%E5%8D%95%E7%89%87%E6%9C%BA/%E8%B5%84%E6%96%99/STC89C52.pdf",
			// 		fileType:"pdf"
			// 	})
			//     }
	
			}
		}
	
</script>

<style lang="scss" scoped>
	//logo样式
	.User_layput {
		background:
			linear-gradient(to bottom, transparent, #fff 400rpx),
			linear-gradient(to left, #beecd8 20%, #F4E2D8);

		min-height: 80vh;
	}

	.UserInfo {
		display: flex;
		align-items: center;
		justify-content: center;
		flex-direction: column;
		padding: 50rpx 20rpx 50rpx;
	}

	.Team_logo {

		width: 160rpx;
		height: 160rpx;
		border-radius: 50%;
		overflow: hidden;

		image {

			width: 100%;
			height: 100%;
		}
	}

	.nickname {
		font-size: 44rpx;
		color: #333;
		padding: 50rpx 0;
	}

	//用户页面列表样式
	.secton {
		width: 690rpx;
		margin: 50rpx auto;
		border: 1rpx solid #eee;
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

	//弹出层popup样式
	.info_popup {
		width: 400rpx;
		background: #fff;
		padding: 30rpx;
		border-radius: 20rpx;
	}

	.popup_Header {
		display: flex;
		justify-content: space-between;
		align-items: center;
		margin-bottom: 20rpx;
	}

	.popup_title {
		color: #676767;
	}

	.close_popup {
		padding: 6rpx;
	}
	.Team_popup{
		width: 100%;
		background: #fff;
		padding: 60rpx;
		border-radius: 30rpx 30rpx 0 0;
		overflow: hidden;
	}	
</style>