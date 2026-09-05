#ifndef TCPNET_H
#define TCPNET_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress> //tcp客户端头文件
#include "QImage"
#include "QFile"
#include "QFileDialog"
#include "QString"
#include <QCompleter>//"
class TCPnet
{
public:
    const int TEMPERATURE_PROBLEM = 1;
    const int HUMITY_PROBLEM = 2;
    const int WATER_LEVEL_PROBLEM = 4;
    const int PH_PROBLEM = 8;
    TCPnet();
    //QTcpSocket *tcpClient ;//TCP客户端
    QFile *localFile;     // 要发送的文件
    qint64 totalBytes;    // 发送数据的总大小
    //    qint64 bytesWritten;  // 已经发送数据大小
    //    qint64 bytesToWrite;  // 剩余数据大小
    qint64 payloadSize;   // 每次发送数据的大小(64k) 未用到
    QString fileName;     // 保存文件路径
    QByteArray outBlock;  // 数据缓冲区，即存放每次要发送的数据块

    QImage image;//图片
    QString currentImageName;//图片名
    volatile bool isOk;
    QStringList hostWordList, portWordList;
    QByteArray encode_pngBase64(const QImage&image);

    QHostAddress serverIP;
    qint16 serverport = 25565;

    void openFile();
    void send();
    int connectServer();
    void SendPicture();
    void SendEnvir_Parameter();
    void disconnectServer();
    void SendAbnormal_Message();
    uchar abnormal_code_encode();

};

#endif // TCPNET_H
