from Socket.sql import database

DB1 = database("BinFile",{
        "ID" : "INT",
        "Name" : "VARCHAR(255)",
        "Time" : "TIMESTAMP",
        "Image" : "LONGBLOB",
        "Size" : "INT"
        })
DB2 = database("Devices",{
        "ID" : "INT",
        "Name" : "VARCHAR(255)",
        "Time" : "TIMESTAMP",
        "Image" : "LONGBLOB",
        "Size" : "INT"
        })
DB3 = database("SensorData",{
        "ID" : "INT",
        "Name" : "VARCHAR(255)",
        "Time" : "TIMESTAMP",
        "Image" : "LONGBLOB",
        "Size" : "INT"
        })
with open("pestToServer/LuoTianYI.jpg", "rb") as f:
    Bin = f.read()
    Size = Bin.__len__()
    InsertInfo = {
        "ID" : 1,
        "Name":"LuoTianYi.jpg",
        "Time" : "Now()",
        "Size" : Size,
        "Image" : Bin
    }
    print(Size)
    DB.insert(InsertInfo)
