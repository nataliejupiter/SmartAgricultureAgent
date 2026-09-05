#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QWidget>
/*串口相关头文件*/
#include<QtSerialPort/QSerialPort>
#include<QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include<QString>
namespace Ui {
class serialPort;
}

class serialPort : public QWidget
{
    Q_OBJECT

public:
    explicit serialPort(QWidget *parent = nullptr);
    ~serialPort();
    void serialPort_reflesh();
    QStringList lastSerialPort;
    QTimer *serial_reflesh = NULL;
        // Qs lastSerialPort;
private slots: //表示槽函数
    void on_btn_clicked();
    void on_btn_close_clicked();
public slots: //表示槽函数
   // void serial_readyRead();

private:
    Ui::serialPort *ui;
};

#endif // SERIALPORT_H
