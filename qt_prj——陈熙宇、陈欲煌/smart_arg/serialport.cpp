#include "serialport.h"
#include "ui_serialport.h"
#include<QPushButton>
extern QTimer *SerialTimer;
extern QSerialPort *serial ;
extern QStringList lastSerialPort;
serialPort::serialPort(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::serialPort)
{
    ui->setupUi(this);
    this->setWindowTitle("串口配置页面");
    this->setFixedSize(300,200);
     SerialTimer = new QTimer(this);
     SerialTimer->start(500);
     connect(SerialTimer,&QTimer::timeout,this,&serialPort::serialPort_reflesh);    //串口刷新函数
     QPushButton * btn = new QPushButton("打开",this);
     btn->setGeometry(80,120,60,40);
     connect(btn,SIGNAL(clicked(bool)),this,SLOT(on_btn_clicked()));
     QPushButton * btn_close = new QPushButton("关闭",this);
     btn_close->setGeometry(200,120,60,40);
     connect(btn_close,SIGNAL(clicked(bool)),this,SLOT(on_btn_close_clicked()));
//     connect(serial,&QSerialPort::readyRead,this,&serialPort::serial_readyRead);     //串口读取函数
}
#include<QMessageBox>
#include <QDebug>
 // void serialPort::serial_readyRead()
 // {
 //     QString ReceiveData;
 //     ReceiveData = serial->readAll();
 //     qDebug()<<ReceiveData;
 //     QMessageBox::information(this,QString::fromUtf8("串口提示"),QString::fromUtf8("接收成功"));
 // }
serialPort::~serialPort()
{
    delete ui;
}

void serialPort::serialPort_reflesh()
{

    QStringList newSerialPort;      //定义一个容器（局部变量），用于存储可用端口
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        newSerialPort += info.portName();
    }
    if(newSerialPort.size() != lastSerialPort.size())   //如果发现新的串口
    {
        lastSerialPort = newSerialPort;                //将新的串口序列存储起来
                ui->serialList->clear();                       //清除旧的串口列表
                ui->serialList->addItems(newSerialPort);       //将新的串口列表写入值serialList
    }
}

void serialPort::on_btn_clicked()
{
    serial->setPortName(ui->serialList->currentText());
    // serial->setBaudRate()
    // int current_number =ui->boundrate->currentIndex();
    // if(current_number == 0)
    // {
    //     serial->setBaudRate( QSerialPort::Baud9600);
    // }
    // else if(current_number == 1)
    // {
    //     serial->setBaudRate( QSerialPort::Baud4800);

    // }
    // else if(current_number == 2)
    // {

    //     serial->setBaudRate( QSerialPort::Baud19200);
    // }

    // else if(current_number == 3)
    // {
    //     serial->setBaudRate( QSerialPort::Baud38400);
    // }

    // else if(current_number == 4)
    // {
    //     serial->setBaudRate( QSerialPort::Baud115200);
    // }

    // current_number = ui->stopbit->currentIndex();

    // if(current_number == 0)
    // {
    //     serial->setStopBits(QSerialPort::OneStop);
    // }
    // else if(current_number == 1)
    // {
    //     serial->setStopBits( QSerialPort::OneAndHalfStop);

    // }

    // current_number = ui->calibrate->currentIndex();

    // if(current_number == 0)
    // {
    //     serial->setParity( QSerialPort::NoParity);

    // }
    // else if(current_number == 1)
    // {
    //     serial->setParity( QSerialPort::OddParity);
    // }
    // else if(current_number == 2)
    // {
    //     serial->setParity( QSerialPort::EvenParity);
    // }
    serial->setParity( QSerialPort::NoParity);
    serial->setDataBits( QSerialPort::Data8);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setBaudRate( QSerialPort::Baud115200);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    if( !serial->open(QIODevice::ReadWrite))
    {
        //qDebug()<<serial->open(QIODevice::ReadWrite);
        QMessageBox::information(this,QString::fromUtf8("串口打开失败"),QString::fromUtf8("请确认串口是否正确连接！"));

        return ;
    }

    QMessageBox::information(this,QString::fromUtf8("串口提示"),QString::fromUtf8("串口打开成功！"));
}
void serialPort::on_btn_close_clicked()
{

}
