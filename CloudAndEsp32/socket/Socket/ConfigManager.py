import threading
from datetime import datetime
import time
import json
import os

DefaultLogPath = "Logs"
DefaultConfigPath = "config.json"
DefaultConfig = {
    "Host": "8.152.218.172",
    "SocketPort": 25565,
    "WebSocketPort": 25564,
    "LastID":1,
    "LastDeleteDataTime":time.time(),
    "DeleteDataInterval" : 86400,
    "DeleteTableList" : ["SensorData","BinFile"],
    "MaxStorageTime" : 30 * 86400,
    "MaxHeartInterval" : 30,
    "HeartScanInterval": 30
}
# 配置/日志管理器
class ConfigManager():

    def __init__(self,ConfigPath:str = DefaultConfigPath,LogsPath:str = DefaultLogPath) -> None:
        self.LogsPath = LogsPath
        self.configPath = ConfigPath
        if os.path.exists(self.LogsPath) == False:
            os.makedirs(self.LogsPath,exist_ok=True)
        if os.path.exists(self.configPath) == False:
            self.initConfig()
            self.config = DefaultConfig
        else:
            self.config = self.readConfig()

    def WriteLogs(self,Str:str):
        if os.path.exists(self.LogsPath) == False:
            os.makedirs(self.LogsPath,exist_ok=True)
        with open(f"{self.LogsPath}/{datetime.today().date()}.txt","a",encoding="utf8") as f:
            now = datetime.now().strftime("%H:%M:%S")
            f.write(f"[{now}] "+str(Str) + "\n")
        print(f"[{now}] "+str(Str) + "\n")

    # 读取配置 
    def readConfig(self):
        # 如果不存在配置文件
        if os.path.exists(self.configPath) == False:
            self.initConfig()
            return
        # 读取配置
        with open(self.configPath,"r") as f:
            Str = f.read()
            Json = json.loads(Str)
            return Json
    # 保存配置
    def SaveConfig(self):
        with open(self.configPath,"w+") as f:
            Str = json.dumps(self.config)
            f.write(Str + "\n")
    # 恢复默认配置
    def initConfig(self):
        with open(self.configPath,"w+") as f:
            # 写入默认配置
            Str = json.dumps(DefaultConfig)
            f.write(Str)
    # 当退出时保存配置
    def __del__(self):
        self.SaveConfig()