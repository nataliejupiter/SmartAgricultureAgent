from sql import database
from Socket.ConfigManager import ConfigManager
from testSocket import SocketServer
from Socket.device import Device
from Socket.socketServer import WebSocketServer,Websocket

import socket
import base64
import threading
import json
import time

HOST = "8.152.218.172"
class server(SocketServer,ConfigManager,WebSocketServer):
    def __init__(self) -> None:
        # 配置初始化
        ConfigManager.__init__(self)
        hostname = socket.gethostname()
        host = socket.gethostbyname(hostname)
        SocketPort = self.config["SocketPort"]
        WebsocketPort = self.config["WebSocketPort"]
        SocketServer.__init__(self,HOST,SocketPort)
        WebSocketServer.__init__(self,HOST,WebsocketPort)

        # 数据表初始化
        self.Devices = database("Devices",{
        "ID":"INT Primary key",\
        "Name":"VARCHAR(20)",\
        "AssociatedDevices":"INT",\
        "LastOnlineTime":"TIMESTAMP",\
        })
        self.SensorData = database("SensorData", {
        "ID":"INT",\
        "ReceiveTime":"TIMESTAMP DEFAULT Now()",\
        "Temp":"FLOAT",\
        "Wet":"FLOAT",\
        "PH":"FLOAT",\
        "WaterLevel":"FLOAT"
        })
        self.BinFile = database("ImageBinFile",{
        "ID" : "INT",\
        "Name" : "VARCHAR(255)",\
        "Time" : "TIMESTAMP",\
        "Image" : "LONGBLOB",
        "Size" : "INT"
        })
        self.InstructList : dict[str:function] = {}
        self.OnlineDevicesList : dict[int:Device] = {}
        self.OnlineDevicesManageThread = threading.Thread(target=self.RefreshOnelineDevicesList)
        self.OnlineDevicesManageThread.start()
        self.InstructList_Init()
        self.WriteLogs(f"服务器已开启,IP:{host},SocketPort:{SocketPort},WebsocketPort:{WebsocketPort}")
    def  deal_Thread(self, connect: Websocket | socket.socket, address: str = None):
        # 接收数据并解析
        ReceiveBin = connect.recv(1024)
        print(ReceiveBin) 
        try:
            ReceiveDict = json.loads(ReceiveBin)
            if "ID" not in ReceiveDict:
                self.WriteLogs(f"来自{address}未包含ID信息")
                connect.send(base64.encode("未包含ID信息"))
                return
            ID = ReceiveDict["ID"]
            # 加入在线列表
            
        except Exception as e:
            print(e)
        self.OnlineDevicesList[ID] = self.Devices_Create(connect,ID,address)
        self.WriteLogs(f"ID:{ID}(IP:{address})上线")
        self.Instruct_deal(ReceiveDict,self.OnlineDevicesList[ID])
        while connect._closed == False:
            try:
                
                ReceiveBin = connect.recv(1024)   
                ReceiveDict = json.loads(ReceiveBin)
                print(ReceiveBin)
                self.Instruct_deal(ReceiveDict,self.OnlineDevicesList[ID])
                self.OnlineDevicesList[ID].updateOlineTime()
            except Exception as e:
                print(e)
                print("deal_Thread WhileTrue")
                return

    def RefreshOnelineDevicesList(self):
        while True:
            NowTime = time.time()
            underlineList = []
            for ID in self.OnlineDevicesList.keys():
                if NowTime > self.OnlineDevicesList[ID].LastAnswerTime + self.config["MaxHeartInterval"]:
                    IP = self.OnlineDevicesList[ID].address
                    self.WriteLogs(f"ID:{ID}(IP:{IP})已离线")
                    underlineList.append(ID)
            for ID in underlineList:
                self.Devices_Del(ID)
            time.sleep(self.config["HeartScanInterval"])
    
    def GetNewID(self) -> int:
        self.config["LastID"] += 1
        return self.config["LastID"]
    # 对发来的指令进行处理
    def Instruct_deal(self,ReceiveDict:dict,Device:Device):
        # 如关联设备在线，则将消息转发
        AssociatedID = Device.AssociatedDevices
        if AssociatedID in self.OnlineDevicesList:
            self.OnlineDevicesList[AssociatedID].connect.send(json.dumps(ReceiveDict).encode())
        try:
            InsKind = ReceiveDict["Kind"]
            Ins = self.InstructList[InsKind]
            Ins(ReceiveDict,Device.connect)
        except:
            pass

    # 命令列表初始化
    def InstructList_Init(self):
        self.InstructList["NewDevice"] = self.Ins_NewDevice
        self.InstructList["Img"] = self.Ins_Img
        self.InstructList["EnvParams"] = self.Ins_EnvParams
        self.InstructList["Associate"] = self.Ins_AssociatedDevices
    
    def Ins_NewDevice(self,RecvDict : dict,connect:socket.socket):
        # 发送新ID
        ID = self.GetNewID()
        connect.send(json.dumps({"Kind":"NewID","NewID":ID}).encode())
        self.WriteLogs(f"新设备入网,分配ID:{ID}")
        device = self.OnlineDevicesList[RecvDict["ID"]]
        device.ID = ID
        if "Name" in RecvDict:
            device.Name = RecvDict["Name"]
        else:
            device.Name = "NoName"
        if "AssociatedDevices" in RecvDict:
            device.AssociatedDevices = RecvDict["AssociatedDevices"]
        # 更新在线列表中的数据
        del self.OnlineDevicesList[RecvDict["ID"]]
        self.OnlineDevicesList[ID] = device
        self.Devices.insert(device.toDict())

    def Ins_AssociatedDevices(self,RecvDict : dict,connect:socket.socket):
        ID = RecvDict["ID"]
        AssociatedID = RecvDict["AssociatedDevices"]
        if "AssociatedDevices" in RecvDict:
            self.OnlineDevicesList[ID].AssociatedDevices = RecvDict["AssociatedDevices"]
        self.Devices.updateData(ID,{"AssociatedDevices":AssociatedID})

    def Ins_Img(self,RecvDict : dict,connect:socket.socket):
        ID   = RecvDict["ID"]
        Size = RecvDict["Size"]
        Name = RecvDict["Name"]
        print("开始接收图片")
        print(f"图片大小{int(Size / 1024)}KB")
        Bin = connect.recv(Size)
        while True:
            BinLen = len(Bin)
            if(BinLen >= Size):
                break
            print(f"当前已接收{int(BinLen/1024)}KB")
            Bin += connect.recv(Size-BinLen)
        with open(Name,"wb") as f:
            f.write(Bin)
        print("接收完毕")
    def Ins_EnvParams(self,RecvDict : dict,connect:socket.socket):
        InsertInfo = {
            "ID" : RecvDict["ID"],
            "Temp" : RecvDict["Temp"],
            "Wet" : RecvDict["Wet"],
            "WaterLevel" : RecvDict["WaterLevel"],
            "PH" : RecvDict["PH"]
        }
        self.SensorData.insert(InsertInfo)
    # 建立新的设备连接
    def Devices_Create(self,connect : socket.socket,ID : int,address : str):
        try:
            AssociatedID = self.Devices.IDquery(ID)[0][2]
        except:
            AssociatedID = None
        NewDevice = Device(connect,ID,address,None,AssociatedID)
        return NewDevice
    # 将设备插入数据库中保存
    def Devices_Update(self,Device:Device):
        InsertInfo = Device.toDict()
        del InsertInfo["ID"]
        self.Devices.updateData(InsertInfo)
    # 将设备移除在线列表
    def Devices_Del(self,ID):
        self.Devices_Update(self.OnlineDevicesList[ID])
        del self.OnlineDevicesList[ID]
    # 用于支持with方法，无须调用
    def __enter__(self):
        return self
    def __exit__(self,type,value,trace):
        self.SaveConfig()
        self.socket.close()
        self.WriteLogs(f"success to close {self.host}:{self.port} server")

        
if __name__ == "__main__":
    srv = server()

