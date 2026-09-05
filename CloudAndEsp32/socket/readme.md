# 服务器通讯协议
### 服务器IP地址与端口号:
host = `123.60.15.215`  
port = `25565`
### 通信方式  
基于TCP/IP协议的Socket服务器
### 通信包格式
包体参照*JSON*格式  
数据包示例：`{"ID": 1, "Name": "SmtAgt", "Kind": "NewDevice", "AssociatedDevices": 2, "LastOnlineTime": "Now()"}`  
*Kind*标识了数据包类型  
*Kind*目前共有四个类型，共有四个类型,分别为:`STATUE`、`Instruct`、`NewDevice`、`Img`,服务器会根据*Kind*的值来对数据包进行分类处理  
##### 当*Kind* = `NewDevice`时:  
代表该设备第一次联网，需要进行初始化  
数据包中仅需包含`{"ID": 0}`  ，后服务器另会分配一个ID，此为该设备的唯一ID
example:`{"ID": 0}`  
##### 当*Kind* = `STATUE`时:
代表此包为智慧农业设备的环境监测数据  
数据包中应包含的内容有:  
`ID`、`Temperature`、`PH`、`ReceiveTime`、`Wet`  
其中，除ID外数据可以缺省（但不建议）  
ReceiveTime默认返回字符串`Now()`即可  
或返回当前日期（较为复杂，不推荐）：  
example: `2024-10-21 20:44:20`
##### 当*Kind* = `Img`时:
数据包示例：`{"ID": 1, "Name": "SmtAgt", "Time": "Now()","Image":"*你的二进制文件（不仅限于图片，任何文件都可以）*"}`
##### 三个数据表的结构
### ENVDATA
`
{  
"ID":"INT",  
"ReceiveTime":"TIMESTAMP DEFAULT Now()",  
"Temperature":"FLOAT",  
"Wet":"FLOAT",  
"PH":"FLOAT",  
}  
`
###### Devices
`
{  
"ID":"INT Primary key",  
"Name":"VARCHAR(20)",  
"AssociatedDevices":"INT",  
"LastOnlineTime":"TIMESTAMP",  
}  
`
###### Image   
`
{  
"ID" : "INT",  
"Name" : "VARCHAR(255)",  
"Time" : "TIMESTAMP",  
"Image" : "LONGBLOB",  
}  
`
###### 心跳进程  
服务器包含在线监测  
当连续五秒没有收到来自服务端的数据时，会将设备认为离线  
可以每隔一段时间向服务器发送空数据包，例如`{}`以保持在线  

