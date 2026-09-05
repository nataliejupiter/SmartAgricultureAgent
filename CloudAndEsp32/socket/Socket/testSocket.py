import socket
import threading

class SocketServer():
    def __init__(self,host:str,port:int) -> None:
        self.host = host
        self.port = port
        self.socket = socket.socket()
        self.socket.bind((host,port))
        self.socket.listen()
        self.listenthread = threading.Thread(target=self.listen)
        self.listenthread.start()
    
    def listen(self) -> None:
        while True:
            connect,address = self.socket.accept()
            dealThread = threading.Thread(target=self.deal_Thread,args=(connect,address))
            dealThread.start()
    
    def deal_Thread(self, connect : socket.socket, address : str = None):
        ...
    
    def SendBytes(self, connect:socket.socket, data:bytes):
        connect.send(data)

    def Recv1KBytes(self, connect : socket.socket) -> str:
        return connect.recv(1024)