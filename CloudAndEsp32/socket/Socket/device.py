import socket
import time

class Device():
    def __init__(self,
                 connect:socket.socket,
                 ID : int,address :str,
                 Name:str = None,
                 AssociatedDevices:int = None,
                 LastAnswerTime : float = time.time()) -> None:
        self.ID = ID
        self.connect = connect
        self.address = address
        self.name = Name
        self.AssociatedDevices = AssociatedDevices
        self.LastAnswerTime = LastAnswerTime

# 转化为字典，以便插入数据库
    def toDict(self):
        return {
            "ID":self.ID,
            "name":self.name,
            "AssociatedDevices":self.AssociatedDevices,
            "LastOnlineTime":"Now()"
        }

    def updateOlineTime(self,time:float = time.time()):
        self.LastAnswerTime = time

        