# 客户端程序

import socket
import json
import time
import threading
import base64

IP = '8.152.218.172'
SERVER_PORT = 25564
BUFLEN = 1024

dataSocket = socket.socket()

# sock.connect(("8.152.218.172",25564))
dataSocket.connect((IP, SERVER_PORT))

while True:
    # 从终端中读入用户输入的字符串
    toSend = input(">> ")
    if toSend == '':
        break
    elif toSend == "exit":
        break
    # 发送消息，也要编码为bytes
    dataSocket.send(toSend.encode())
    print(f"客户端发送的消息是：{toSend}")

    # 等待接收服务器的消息，阻塞
    recved = dataSocket.recv(BUFLEN)
    # 如果返回空bytes，表示对方关闭了连接
    if not recved:
        break
    print(f"接收到服务端消息：{recved.decode()}")

dataSocket.close()

# ImgList = ["StarDust.jpg","LuoTianYi.jpg"]
# def sendmess(List):
#     for Name in List:
#         b = open(Name,"rb")
#         Img = b.read()
#         sock.send(json.dumps({"ID":1,"Kind":"Img","Size":len(Img),"Name":Name}).encode())
#         time.sleep(0.1)
#         sock.send(Img)
#         time.sleep(1)

# sendmess(ImgList)

# InsertInfo = {
#     "Kind" : "Associate",
#     "ID" : 2,
#     "AssociatedDevices":3
# }
# dataSocket.send(json.dumps(InsertInfo).encode())

# print(dataSocket.recv(1024))


# # 发送消息到服务器
# ws.send(json.dumps(InsertInfo).encode())
# ws.send(json.dumps(InsertInfo).encode())
# # ws.close()
