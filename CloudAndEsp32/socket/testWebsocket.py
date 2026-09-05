from websocket import create_connection
import json

InsertInfo = {
    "Kind" : "EnvParams",
    "ID" : 11,
    "Temp" : 37.5,
    "Wet" : 66.6,
    "WaterLevel" : 15,
    "PH" :7.7
}


# 创建 WebSocket 连接
ws = create_connection("ws://8.152.218.172:80")  # websocket默认端口为80

# 发送消息到服务器
ws.send(json.dumps(InsertInfo).encode())

# 关闭连接
ws.close()
