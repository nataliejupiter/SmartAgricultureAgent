<template>
	<view>
		<view>留言列表</view>
		<!-- Display the list of messages -->
		<view>
			<view v-for="(msg, index) in messages" :key="index">{{ msg }}</view>
		</view>

		<input type="text" v-model="message" placeholder="请输入消息" />
		<button @click="sendMessage">发送</button>
		<button @click="connectWebSocket">连接</button>
	</view>
</template>

<script>
	export default {
		data() {
			return {
				message: "", // User message input
				messages: [], // To store received messages from the WebSocket server
				InsertInfo: { // The data to send, same format as Python dictionary
					"Kind": "EnvParams",
					"ID": 11,
					"Temp": 37.5,
					"Wet": 66.6,
					"WaterLevel": 12,
					"PH": 7.7
				}
			};
		},
		onLoad() {
			this.connectWebSocket(); // Connect to the WebSocket server when the component loads
		},
		methods: {
			connectWebSocket() {
				uni.connectSocket({
					url: 'ws://123.60.15.215:25564',
					success: () => {
						console.log("WebSocket 请求已发送");
					},
					fail: error => {
						console.error("WebSocket 连接失败", error);
					}
				});

				uni.onSocketOpen(() => {
					console.log("WebSocket 连接成功！");
					// 连接成功后再监听消息
					uni.onSocketMessage((res) => {
						console.log("收到消息:", res.data);
						try {
							let parsedData = JSON.parse(res.data);
							this.messages.push(parsedData);
						} catch (error) {
							console.error("解析 WebSocket 消息失败:", error);
						}
					});
				});

				uni.onSocketError((error) => {
					console.error("WebSocket 连接错误", error);
				});

				uni.onSocketClose(() => {
					console.log("WebSocket 连接关闭");
				});
			},

			sendMessage() {
				// Convert the InsertInfo object to a JSON string and send it to the WebSocket server
				const messageToSend = JSON.stringify(this.InsertInfo);

				uni.sendSocketMessage({
					data: messageToSend // Send the stringified InsertInfo data
				});

				// Optionally, you can add the sent message to the local message list for display
				this.messages.push(this.InsertInfo); // Add to message list
				this.message = ""; // Clear the input field after sending
			}
		}
	};
</script>