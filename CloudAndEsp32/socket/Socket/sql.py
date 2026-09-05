import pymysql
import socket
import json
import threading

# IP/端口号及数据库
DB = "smartagr"
HOST = "8.152.218.172"
PORT = 3306
# 用户名
USER = "lily"
PASSWORD = "lilylily"
# 数据库基类
class database:
    def __init__(self,
                 table:str,
                 tableStructure:dict,
                 host:str = HOST,
                 port:int = PORT,
                 user:str = USER,
                 password:str = PASSWORD,
                 db:str = DB,) -> None:
        # 如果在云端运行，则使用本地回环地址
        connect = pymysql.connect(
            host = host,
            port = port,
            user = user,
            passwd = password,
            charset = "utf8"
            )
        
        self.connect = connect
        self.cursor = connect.cursor()
        self.table = table
        self.tableStructure = tableStructure
        # 初始化数据库
        self.cursor.execute(f"CREATE DATABASE IF NOT EXISTS {db}")
        self.cursor.execute("USE " + db)
        cmd = ""
        for key in tableStructure.keys():
            cmd += key + " " + tableStructure[key] + ","
        self.cursor.execute(f"CREATE TABLE IF NOT EXISTS {table}({cmd[:-1]})")
        print(f"connect to {self.table}")

    #接收所有输出
    def fetchall(self):
        print(self.cursor.fetchall())

    # 插入数据
    def insert(self,data:dict):
        KeyValue = ",".join(map(str,[data[key] for key in data.keys()]))
        sql = "INSERT INTO %s (%s) values (%s)"%(self.table,",".join(data),KeyValue)
        self.cursor.execute(sql)
        self.connect.commit()
        
    def insertJson(self,data:str):
        dict = json.loads(data)
        self.insert(dict)
    # 根据ID查询
    def IDquery(self,id:int):
        self.cursor.execute(f"SELECT * FROM {self.table} where id = {id}")
        return self.cursor.fetchall()

    # 查询key为data的对象的returnData
    def query(self,key : str,data,returnData : str = "*") -> str:
        self.cursor.execute(f"SELECT {returnData} FROM {self.table} where {key} = {data}")
        return self.cursor.fetchall()

    def updateData(self,ID:int,data:dict):
        updateData = ""
        for key in data:
            Value = data[key]
            if isinstance(Value,str) and Value != "Now()":
                if Value[0] != '\'' and Value[-1] != '\'':
                    Value = f"\'{Value}\'"
            updateData += f"{key}={Value},"
        lock = threading.Lock()
        lock.acquire()
        self.cursor.execute(f"update {self.table} set {updateData[:-1]} where ID={ID}")
        self.connect.commit()
        lock.release()

    # 展示数据库中所有数据
    def ShowAllData(self) -> tuple:
        self.cursor.execute(f"SELECT * FROM {self.table}")
        all = self.cursor.fetchall()
        print(all)
        return all
    
    # 用于支持with方法，无须调用
    def __enter__(self):
        return self
    def __exit__(self,type,value,trace):
        self.cursor.close()
        self.connect.close()
        print(f"exit {self.table}")

if __name__ == "__main__":
    pass
