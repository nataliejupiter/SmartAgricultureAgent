 #ifndef MAINMONITOR_H
#define MAINMONITOR_H

#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QMenuBar>


/*绘图相关*/
#include "QtCharts/QChartView"
#include "QtCharts/QSplineSeries"
#include <QtCharts/QValueAxis>
#include <QChart>

#include "serialport.h"
#include "aboutus.h"
#include "serialdate.h"
#include "abnormal.h"
/*串口相关头文件*/
#include<QtSerialPort/QSerialPort>
#include<QtSerialPort/QSerialPortInfo>
#include <QTimer>

//#include <opencv2/opencv.hpp>
#include <opencv2/opencv.hpp>

#include"temperture_page.h"
#include"wet_page.h"
#include "waterlevel_page.h"
#include "ph_page.h"
#include <vector>
#include"set_help.h"

#include "my_sql.h"
#include "tcpnet.h"
//#include <opencv2/opencv.hpp>
//using namespace cv;
namespace Ui {
class mainMonitor;

}

/*植物类，包含预设的*/
class plants{
private:
    float temperature[2];
    float wet[2];
    float ph[2];
    float light[2];
    float shinyTime ;
    friend temperture_page;
    friend wet_page;
    friend PH_page;
    friend waterlevel_page;
public:
    void set_plants(float temprature_high,float temperature_low,
                    float wet_high,float wet_low,
                    float ph_high,float ph_low,
                    float shinytime);
};


class mainMonitor : public QWidget
{
    Q_OBJECT

//    QChart* chart = nullptr;
//    QLineSeries *series = nullptr;
public:
    explicit mainMonitor(QWidget *parent = nullptr);
    ~mainMonitor();
    TCPnet *my_tcpnet = NULL;
    serialPort *mySerialPort= NULL;
    aboutus *myAboutus = NULL;
    serialdate *mySerialdate= NULL;
    abnormal *myAbnormal = NULL;
    temperture_page *Temper_page=NULL;
    wet_page *Wet_page=NULL;
    PH_page *myPH_page=NULL;
    waterlevel_page *mywater_level_page=NULL;

    QTimer *picture_refleshTimer = NULL;

    //QTimer *TemperatureTimer = NULL;
    cv::Mat image;

    QPen pen_tempreature;
    QPen pen_waterlevel;
    QPen pen_wet;
    QPen pen_PH;


    //my_sql
public slots:
      void serial_readyRead();
private slots:
    void SerialHistoricalDatePage();
    void SerialSetPage();
    void TemperatureSetPage();
    void WetParameterSetPage();
    void WaterLevelSetPage();
    void AboutusPage();
    void PHSetPage();
    void SerialTimeout_Event();
    void PictureReflesh();
//    QMenuBar *menuBar;

    void on_pushButton_abnormal_clicked();

    void on_Button_Button_waterlevel_licked();

    void on_Button_temperature_clicked();

    void on_Button_waterlevel_clicked();

    void on_Button_wet_clicked();
    void drawingline();
    void on_Button_start_clicked();

    void on_Button_sendPicture_clicked();

    void on_Button_ph_clicked();

private:
    Ui::mainMonitor *ui;
};

class systemData{
public:
    float showing_temperature=25.000;
    float terperature_limit[2];  //温度限制数据，第0个数为上线，第一个数为下限，下面的数据也相同
    float showing_wetdata=78.00;
    float wet_limit[2];
    float showing_waterleveldata=12.00;
    float waterlevel_limit[2];
    float showing_PH=5.0;
    uchar showing_diseases=0;
    float showing_sunshine=56.0;
    float sunshine_limit[2];
    QVector<float> Temperature;
    QVector<float> Waterlevel;
    QVector<float> Wet;
    QVector<float> PH;
    int drawing_flag=0;//指明绘制的曲线类型

    void push(float temperature,float wet,float waterlevel,float Ph);
private:
    int max_contain = 1000; //每个vector最多存储的数据量


};
class situationSattus
{
public:
    uchar wait_to_solve_flag = 0;    //突发情况待处理标志位，当出现特殊情况时置1，解决后置0
    uchar water_pormble_number = 0;
    uchar wet_promble_number = 0;
    uchar temperature_promble_number = 0;
    uchar ph_problem_number=0;
    uchar  diseases_number=0;
    uchar sunshine_problem_number=0;

    uchar water_wait_to_solve_flag = 0;
    uchar temperature_wait_to_solve_flag = 0;
    uchar wwt_wait_to_solve_flag = 0;
    uchar ph_wait_to_solve_flag=0;
    uchar diseases_flag=0;
    uchar sunshine_wait_to_solve_flag=0;

    uchar water_level_message_not_sendflg = 0;
    uchar wet_message_not_sendflg = 0;
    uchar temperature_message_not_sendflg = 0;
    uchar ph_message_not_sendflg = 0;
    uchar disease_message_not_sendflg = 0;

    int sum_promble = 0;

    uchar disease_serial = 0; //病虫害编号
    uchar Message_to_be_send_flag = 0;

};


#endif // MAINMONITOR_H
