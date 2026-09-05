#include "tcpnet.h"
#include "mainmonitor.h"
#include "qbuffer.h"
#include "widget.h"
#include "mainwindow.h"
#include "QMessageBox"
#include"QDebug"
#include"QImage"
#include "QThread"
QTcpSocket tcpClient ;//TCP客户端
extern systemData systemData1;//初始化数据
extern situationSattus situationSattus1;//异常状态数据
TCPnet::TCPnet()
{
    //connectServer();
    //tcpClient.setSocketOption(QAbstractSocket::KeepAliveOption, 1); // 启用保活
}
int TCPnet::connectServer()
{
    serverIP.setAddress("123.60.15.215");
    qDebug()<<serverIP;
    tcpClient.connectToHost(serverIP,serverport);
    if (!tcpClient.waitForConnected(5000))
    {
        //QMessageBox::information(this,)
        qDebug() << "Connection failed:" << tcpClient.errorString();
        return -1;
    }
    qDebug()<<"Connection successfully!";
    //this->SendEnvir_Parameter();
    return 1;
    //SendPicture();
}

void TCPnet::disconnectServer()
{
    tcpClient.disconnectFromHost();
}
void TCPnet::SendPicture()
{

    QFile imageFile("image_storage/image.jpg");
    if (!imageFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Error: Cannot open image file";
        return;
    }
    QByteArray imageData = imageFile.readAll();
    QString pic_size = QString::number(imageFile.size());
    QByteArray tcp_head = "{\"Kind\":\"Img\",\"ID\":10,\"Size\":" + pic_size.toLatin1() +",\"Name\":\"test.jpg\"}";
    imageFile.close();
    // 发送包头
    if (tcpClient.write(tcp_head) == -1) {
        qDebug() << "Write head error:" << tcpClient.errorString();
        return;
    }
    QThread::msleep(50);//阻塞延时50ms
//发送图片数据
    if (tcpClient.write(imageData) == -1) {
        qDebug() << "Write error:" << tcpClient.errorString();
        return;
    }
    if (!tcpClient.waitForBytesWritten(30000)) {
        qDebug() << "Data transfer timeout";
        return;
    }

    tcpClient.disconnectFromHost();
    qDebug() << "Base64 image data sent!";
}

void TCPnet::SendEnvir_Parameter()
{
    QString temperature = QString::number(systemData1.showing_temperature);
    QString wet = QString::number(systemData1.showing_wetdata);
    QString water_level = QString::number(systemData1.showing_waterleveldata);
    QString ph = QString::number(systemData1.showing_PH);
    QString abnoarml_situation = QString::number(systemData1.showing_diseases);
    QByteArray envir_paramPackage = "{\"Kind\":\"EnvParams\",\"ID\":11,\"Temp\":"+temperature.toLatin1()+",\"Wet\":"+wet.toLatin1()+
                                        ",\"WaterLevel\":"+water_level.toLatin1()+",\"PH\" :"+ph.toLatin1()+"}";
    if (tcpClient.write(envir_paramPackage) == -1) {
        qDebug() << "Write head error:" << tcpClient.errorString();
        return;
    }
}

void TCPnet::SendAbnormal_Message()
{
    this->connectServer();
    QString temperature = QString::number(systemData1.showing_temperature);
    QString wet = QString::number(systemData1.showing_wetdata);
    QString water_level = QString::number(systemData1.showing_waterleveldata);
    QString ph = QString::number(systemData1.showing_PH);

    QString abnoarml_situation = QString::number(this->abnormal_code_encode());
    QByteArray envir_paramPackage = "{\"Kind\":\"EnvParams\",\"ID\":11,\"Temp\":"+temperature.toLatin1()+",\"Wet\":"+wet.toLatin1()+
                                    ",\"WaterLevel\":"+water_level.toLatin1()+",\"PH\" :"+ph.toLatin1()+",\"SituationCode\":"+abnoarml_situation.toLatin1()+"}";
    if (tcpClient.write(envir_paramPackage) == -1) {
        qDebug() << "Write head error:" << tcpClient.errorString();
        return;
    }
    situationSattus1.Message_to_be_send_flag = 0;
    this->disconnectServer();
}

uchar TCPnet::abnormal_code_encode()
{
    uchar code=0,disease = 0;
    if(situationSattus1.temperature_message_not_sendflg)
    {
        code+=TCPnet::TEMPERATURE_PROBLEM;
        situationSattus1.temperature_message_not_sendflg=0;
    }
    if(situationSattus1.wet_message_not_sendflg)
    {
        code+=TCPnet::HUMITY_PROBLEM;
        situationSattus1.wet_message_not_sendflg=0;
    }
    if(situationSattus1.water_level_message_not_sendflg)
    {
        code+=TCPnet::WATER_LEVEL_PROBLEM;
        situationSattus1.water_level_message_not_sendflg=0;
    }
    if(situationSattus1.ph_message_not_sendflg)
    {
        code+=TCPnet::PH_PROBLEM;
        situationSattus1.ph_message_not_sendflg=0;
    }
    if(situationSattus1.disease_message_not_sendflg)
    {
        disease = situationSattus1.disease_serial * 16;
        situationSattus1.disease_message_not_sendflg=0;
    }
    code = code + disease;
    return code;
}
