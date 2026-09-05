#include "mainmonitor.h"
#include "ui_mainmonitor.h"
#include <QMenu>
#include <QMessageBox>
#include "ui_serialport.h"
#include "aboutus.h"
#include "tcpnet.h"

QTimer *SerialTimer=NULL;
QSerialPort *serial = NULL;
QStringList lastSerialPort;

cv::VideoCapture cap;
systemData systemData1;//初始化数据
situationSattus situationSattus1;//异常状态数据
my_sql sql;
plants struberry;
mainMonitor::mainMonitor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainMonitor)
{
    ui->setupUi(this);
    this->setWindowTitle("Main Monitor");
    this->setFixedSize(600,480);



    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *menu_serial = new QMenu("串口",this);
    QMenu *parameter = new QMenu("参数设置",this);
    QMenu *Aboutus=new QMenu("关于",this);
    menuBar->addMenu(menu_serial);                               //串口栏
    menuBar->addMenu(parameter);                          //串口功能栏
    menuBar->addMenu(Aboutus);
    QAction *serial_action1 = new QAction("串口历史数据",this);    //串口界面配置按钮
    QAction *serial_action2 = new QAction("打开串口配置页面",this);              //串口功能界面              //串口功能界面
    QAction *temperatureParameterSet = new QAction("温度参数设置",this);
    QAction *WetParameterSet = new QAction("湿度参数设置",this);
    QAction *WaterLevelParameterSet = new QAction("水位参数设置",this);
    QAction *PHSet = new QAction("PH参数设置",this);
    QAction *aboutus_page=new QAction("关于我们",this);
    menu_serial->addAction(serial_action1);
    menu_serial->addAction(serial_action2);
    parameter->addAction(temperatureParameterSet);
    parameter->addAction(WetParameterSet);
    parameter->addAction(WaterLevelParameterSet);
    parameter->addAction(PHSet);
    Aboutus->addAction(aboutus_page);
    connect(serial_action1,SIGNAL(triggered(bool)),this,SLOT(SerialHistoricalDatePage()));
    connect(serial_action2,SIGNAL(triggered(bool)),this,SLOT(SerialSetPage()));
    connect(temperatureParameterSet,SIGNAL(triggered(bool)),this,SLOT(TemperatureSetPage()));
    connect(WetParameterSet,SIGNAL(triggered(bool)),this,SLOT(WetParameterSetPage()));
    connect(WaterLevelParameterSet,SIGNAL(triggered(bool)),this,SLOT(WaterLevelSetPage()));
    connect(PHSet,SIGNAL(triggered(bool)),this,SLOT(PHSetPage()));
    connect(aboutus_page,SIGNAL(triggered(bool)),this,SLOT(AboutusPage()));

    this->mySerialPort = new serialPort;

    serial = new QSerialPort(this); //为一个串口对象开辟空间
    //串口初始化


    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits( QSerialPort::Data8);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl( QSerialPort::NoFlowControl);
    serial->setParity( QSerialPort::NoParity);
    this->myAboutus = new aboutus;

    this->mySerialdate = new serialdate;
    this->myAbnormal = new abnormal;
    this->Temper_page = new temperture_page;
    this->Wet_page = new wet_page;
    this->myPH_page = new PH_page;
    this->mywater_level_page = new waterlevel_page;
    //曲线图画笔初始化
    pen_tempreature.setColor(QColor("red")); // 设置为红色
    pen_tempreature.setWidth(3); // 设置线宽
    pen_waterlevel.setColor(QColor("blue"));
    pen_waterlevel.setWidth(3);
    pen_wet.setColor(QColor("yellow"));
    pen_wet.setWidth(3);
    pen_PH.setColor(QColor("pink"));
    pen_PH.setWidth(3);

//    chart = new QChart();
//    // 构建折线系列对象
//    series = new QLineSeries();
//    /*创建所要绘制的二维图像的对象*/
    QChart* chart = new QChart();
//    // 构建折线系列对象
    QLineSeries *series = new QLineSeries();
    QVector<uchar> TemperatureData; //数据容器，温度
    for(int x = 0;x<200;x++)
    {
        series->append(x,x);    //压入数据
    }
    chart->resize(1800,1600);
    chart->addSeries(series);
    chart->createDefaultAxes();
//    chart->setTitle("环境参数");
    series->setName("温度");
    chart->axes().at(0)->setTitleText("时间");    //一般X轴索引为0
    chart->axes().at(1)->setTitleText("温度");    //一般X轴索引为0
    series->setPen(pen_tempreature);
     ui->graphicsView->setChart(chart);
    //ui->graphicsView->clearFocus();
    picture_refleshTimer=new QTimer(this);
    picture_refleshTimer->start(50);

    cap = cv::VideoCapture(0);

    this->my_tcpnet = new TCPnet;

     struberry.set_plants(25.0,15.0,
                     80.0,60.0,
                     6.5,5.5,
                     12.5);

    connect(serial,&QSerialPort::readyRead,this,&mainMonitor::serial_readyRead);     //串口读取函数
    connect(picture_refleshTimer,&QTimer::timeout,this,&mainMonitor::PictureReflesh);
    connect(SerialTimer,&QTimer::timeout,this,&mainMonitor::SerialTimeout_Event);    //串口刷新函数



}
/*************
*brief: 字符串转换函数，将输入的字符串转换为整型数组进行输出
*param: input：输入字符串，类型为std::string
*       output: 输出的数组的首地址，类型为int
*return: void
**************/
void string_trans(std::string input,int *output)
{

    int i = 0;
    int bit_flag = 0;//位标志，最高为1
    int byte_flag = 0;//字节数标志位
    int temp = 0;
    while (input[i] != '\0')
    {
        //printf("%s", input[i]);
        if (bit_flag == 0)
        {
            temp = 0;
            if (input[i] < 96)
            {
                temp += (input[i] - 48) * 16;
            }
            else
            {
                temp += ((input[i] - 96)+9) * 16;
            }
            bit_flag++;
            i++;
        }
        else
        {
            if (input[i] < 96)
            {
                temp += (input[i] - 48);
            }
            else
            {
                temp += (input[i] - 96)+9;
            }
            *(output + byte_flag) = temp;
            byte_flag++;
            bit_flag = 0;
            i++;
        }
    }
}
/********************
*brief: 数据压入队列操作方法
*param:传感器数据
*return:void
***********************/
 void systemData::push(float temperature,float wet,float waterlevel,float Ph)
{
     if(Temperature.size()==max_contain)
    {
         Temperature.erase(Temperature.begin());
    }
     if(temperature<100)
     Temperature.push_back(temperature);
    if(Waterlevel.size()==max_contain)
    {
        Waterlevel.erase(Waterlevel.begin());
    }
    Waterlevel.push_back(waterlevel);

    if(Wet.size()==max_contain)
    {
        Wet.erase(Wet.begin());
    }
    Wet.push_back(wet);

    if(PH.size()==max_contain)
    {
        PH.erase(PH.begin());
    }
    PH.push_back(Ph);
}


void plants::set_plants(float temprature_high,float temperature_low,
                        float wet_high,float wet_low,
                        float ph_high,float ph_low,
                        float shinytime)
{
    this->temperature[0]=temprature_high;
    this->temperature[1]=temperature_low;
    this->wet[0]=wet_high;
    this->wet[1]=wet_low;
    this->ph[0] = ph_high;
    this->ph[1] = ph_low;
    this->shinyTime = shinytime;
}
/*********************
*brief:串口接收函数，用于实时接收单片机传输的传感器数据，并进行存储
*
*
**********************/
int output[20]={0};
void mainMonitor::serial_readyRead()
{
    QString ReceiveData;
    ReceiveData = serial->readAll().toHex();
    mySerialdate->push_data(ReceiveData);
    string_trans(ReceiveData.toStdString(),output);
    systemData1.showing_temperature=(float(output[2]*256+output[3])/100);
    //systemData1.showing_wetdata=100-(float(output[4]*256+output[5]))/40.96;
    systemData1.showing_wetdata=(float(output[4]*256+output[5])/100);
    systemData1.showing_waterleveldata=(float(output[8]*256+output[9])/100);
    systemData1.showing_PH=(float(output[6]*256+output[7])/100);
    systemData1.push(systemData1.showing_temperature,systemData1.showing_wetdata,systemData1.showing_waterleveldata,systemData1.showing_PH);
    // qDebug()<<systemData1.Temperature;
}
int line_flag=0; //划线标志位，若是为0则画温度线，为1则画湿度线
int reflesh_flag=0;
int situation_refresh_flag = 0;
int param_send_time_flag = 0;
uchar tcp_start_flag = 0;
/*
 * brief:相机画面刷新函数，在次函数中，同时也会执行参数曲线的实时绘制
 */
void mainMonitor::PictureReflesh()
{

    int tcp_status = 0;
    cap>>image;
    cvtColor(image,image,cv::COLOR_BGR2RGB);
    ui->camera->setPixmap(QPixmap::fromImage(QImage(image.data,image.cols,image.rows,QImage::Format_RGB888)));
    reflesh_flag++;
    situation_refresh_flag++;
    param_send_time_flag++;
    //qDebug()<<param_send_time_flag;
    if(param_send_time_flag == 200)
    {

        if(tcp_start_flag == 1)
        {
            tcp_status = my_tcpnet->connectServer();
            if(tcp_status == 1)
            {
                my_tcpnet->SendEnvir_Parameter();//向服务器发送图片数据
                my_tcpnet->disconnectServer();
                //my_tcpnet->tcpClient.disconnectFromHost();
            }
            else
            {
                QMessageBox::information(this,QString::fromUtf8("TCP连接提示"),QString::fromUtf8("连接已断开！请尝试重新连接"));
                tcp_start_flag = 0;
            }
        }
        param_send_time_flag = 0;
    }
     if(situation_refresh_flag == 300)
    {
        imwrite("image_storage/image.jpg", image);
        if(tcp_start_flag == 1)
        {
            //tcp_status = my_tcpnet->connectServer();
            if(tcp_status == 1)
            {
                my_tcpnet->SendPicture();//向服务器发送图片数据
                my_tcpnet->disconnectServer();
            }
            else
            {
                QMessageBox::information(this,QString::fromUtf8("TCP连接提示"),QString::fromUtf8("连接已断开！请尝试重新连接"));
                tcp_start_flag = 0;
            }
        }
        Temper_page->data_read();//读取温度临界值
        Wet_page ->data_read(); //读取湿度临界温度
        mywater_level_page  ->data_read();//读取水位临界温度
        if((systemData1.showing_waterleveldata > systemData1.waterlevel_limit[0])&&(situationSattus1.water_wait_to_solve_flag == 0))
        {
            situationSattus1.water_pormble_number ++;//水位高于临界值
            situationSattus1.sum_promble++;
            situationSattus1.water_wait_to_solve_flag = 1;
            situationSattus1.Message_to_be_send_flag = 1;
            situationSattus1.water_level_message_not_sendflg = 1;
        }

        if((systemData1.showing_waterleveldata < systemData1.waterlevel_limit[1])&&(situationSattus1.water_wait_to_solve_flag == 0))
        {
            situationSattus1.water_pormble_number ++;//水位高于临界值
            situationSattus1.sum_promble++;
            situationSattus1.water_wait_to_solve_flag = 1;
            situationSattus1.Message_to_be_send_flag = 1;
            situationSattus1.water_level_message_not_sendflg = 1;
        }

        if((systemData1.showing_temperature > systemData1.terperature_limit[0])&&(situationSattus1.temperature_wait_to_solve_flag == 0))
        {
            situationSattus1.temperature_promble_number++;
            situationSattus1.temperature_wait_to_solve_flag = 1;
            situationSattus1.sum_promble++;
            situationSattus1.Message_to_be_send_flag = 1;
            situationSattus1.temperature_message_not_sendflg = 1;
        }
        if((systemData1.showing_temperature < systemData1.terperature_limit[1])&&(situationSattus1.temperature_wait_to_solve_flag == 0))
        {
            situationSattus1.temperature_promble_number++;
            situationSattus1.temperature_wait_to_solve_flag = 1;
            situationSattus1.sum_promble++;
            situationSattus1.Message_to_be_send_flag = 1;
            situationSattus1.temperature_message_not_sendflg = 1;
        }

        if((systemData1.showing_wetdata>systemData1.wet_limit[0])&& (situationSattus1.wwt_wait_to_solve_flag == 0))
        {
            situationSattus1.wet_promble_number++;
            situationSattus1.sum_promble++;
            situationSattus1.wwt_wait_to_solve_flag = 1;
            situationSattus1.Message_to_be_send_flag = 1;
            situationSattus1.wet_message_not_sendflg = 1;
        }

        if((systemData1.showing_wetdata<systemData1.wet_limit[1])&& (situationSattus1.wwt_wait_to_solve_flag == 0))
        {
            situationSattus1.wet_promble_number++;
            situationSattus1.sum_promble++;
            situationSattus1.wwt_wait_to_solve_flag = 1;
            situationSattus1.Message_to_be_send_flag = 1;
            situationSattus1.wet_message_not_sendflg = 1;
        }
        if((systemData1.showing_sunshine>systemData1.sunshine_limit[0])&& (situationSattus1.sunshine_wait_to_solve_flag == 0))
        {
            situationSattus1.sunshine_problem_number++;
            situationSattus1.sum_promble++;
            situationSattus1.sunshine_wait_to_solve_flag = 1;
            situationSattus1.Message_to_be_send_flag = 1;
        }

        if((systemData1.showing_sunshine<systemData1.sunshine_limit[1])&& (situationSattus1.sunshine_wait_to_solve_flag == 0))
        {
            situationSattus1.sunshine_problem_number++;
            situationSattus1.sum_promble++;
            situationSattus1.sunshine_wait_to_solve_flag = 1;
            situationSattus1.Message_to_be_send_flag = 1;
        }
        if((systemData1.showing_diseases)&& (situationSattus1.diseases_flag== 0))
        {
            situationSattus1.diseases_number++;
            situationSattus1.sum_promble++;
            situationSattus1.diseases_flag= 1;
            situationSattus1.Message_to_be_send_flag = 1;
            situationSattus1.disease_message_not_sendflg = 1;
        }
        situation_refresh_flag = 0;//标志位清零，重新计时
    }
    /**************
     * 绘图标志位
     ***************/
    if(reflesh_flag>=6)
    {
        if(situationSattus1.Message_to_be_send_flag)
        {
            my_tcpnet->SendAbnormal_Message();
            //situationSattus1.Message_to_be_send_flag = 0;
        }
        QString str_temperature = QString::number(systemData1.showing_temperature, 'f', 2);
        ui->lineEdit_temperature->setText(str_temperature);
        QString str_wet = QString::number(systemData1.showing_wetdata, 'f', 2);
         ui->lineEdit_wet->setText(str_wet);
        QString str_waterlevel = QString::number(systemData1.showing_waterleveldata, 'f', 2);
         ui->lineEdit_waterlevel->setText(str_waterlevel);
         QString str_ph = QString::number(systemData1.showing_PH, 'f', 2);
          ui->lineEdit_ph->setText(str_ph);
        if(situationSattus1.wait_to_solve_flag==1)
         {
            //此处添加一个感叹号按键控件，可点击进入处理查看，在在新的页面中将flag清除
        }
        QString str_waterlevel_problem = QString::number(situationSattus1.water_pormble_number);
        QString str_wet_problem = QString::number(situationSattus1.wet_promble_number);
        QString str_temperature_problem = QString::number(situationSattus1.temperature_promble_number);
        situationSattus1.sum_promble=situationSattus1.temperature_promble_number+situationSattus1.wet_promble_number+situationSattus1.water_pormble_number;
        QString str_sum = QString::number(situationSattus1.sum_promble);
        ui->sum->setText(str_sum);
        reflesh_flag=0;
        if(systemData1.drawing_flag ==0)
        {
            QChart* chart = new QChart();
            // 构建折线系列对象
            QLineSeries *series = new QLineSeries();
            for(int x = 0;x<systemData1.Temperature.size();x++)
            {
                //        TemperatureData[x]= x;
                series->append(x,systemData1.Temperature.at(x));    //压入数据
            }
            chart->resize(1800,1600);
            chart->addSeries(series);
            chart->createDefaultAxes();
            series->setName("温度");
            chart->axes().at(0)->setTitleText("时间");    //一般X轴索引为0
            chart->axes().at(1)->setTitleText("温度");    //一般X轴索引为0
            series->setPen(pen_tempreature);
            ui->graphicsView->setChart(chart);
        }
        else if(systemData1.drawing_flag ==1)
        {
            QChart* chart = new QChart();
            //chart->legend()->setLabelColor(Qt::blue);
            // 构建折线系列对象
            QLineSeries *series = new QLineSeries();
            for(int x = 2;x<systemData1.Wet.size();x++)
            {
                //        TemperatureData[x]= x;
                series->append(x,systemData1.Wet.at(x));    //压入数据
            }
            chart->addSeries(series);
            chart->createDefaultAxes();
            series->setName("湿度");
            chart->axes().at(0)->setTitleText("时间");    //一般X轴索引为0
            chart->axes().at(1)->setTitleText("湿度");    //一般X轴索引为0
            series->setPen(pen_wet);
            ui->graphicsView->setChart(chart);
        }
        else if(systemData1.drawing_flag ==2)
            {
                /*创建所要绘制的二维图像的对象*/
                QChart* chart = new QChart();
                // 构建折线系列对象
                QLineSeries *series = new QLineSeries();
            //series->clear();
                for(int x = 2;x<systemData1.Waterlevel.size();x++)
                {
                    //        TemperatureData[x]= x;
                    series->append(x,systemData1.Waterlevel.at(x));    //压入数据
                }

                chart->resize(1800,1600);
                chart->addSeries(series);
                chart->createDefaultAxes();
                //    chart->setTitle("环境参数");
                series->setName("水位");
                chart->axes().at(0)->setTitleText("时间");    //一般X轴索引为0
                chart->axes().at(1)->setTitleText("水位");    //一般X轴索引为0


                series->setPen(pen_waterlevel);
                ui->graphicsView->setChart(chart);
            }


    }
}
void mainMonitor::SerialHistoricalDatePage()
{
     mySerialdate->show();
}

void mainMonitor::SerialSetPage()
{
//     QMessageBox::information(this,QString::fromUtf8("提示"),QString::fromUtf8("show"));
    mySerialPort->show();
}

void mainMonitor::TemperatureSetPage()
{
    Temper_page->show();
}

void mainMonitor::WetParameterSetPage()
{
    Wet_page->show();
}

void mainMonitor::WaterLevelSetPage()
{
    mywater_level_page->show();
}
void mainMonitor::PHSetPage()
{
    myPH_page->show();
    //myAboutus->show();
}
void mainMonitor::AboutusPage()
{
    myAboutus->show();
}
/*串口检测方法*/
void mainMonitor::SerialTimeout_Event()
{
    QStringList newSerialPort;      //定义一个容器（局部变量），用于存储可用端口
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        newSerialPort += info.portName();
    }
    if(newSerialPort.size() != lastSerialPort.size())   //如果发现新的串口
    {
        lastSerialPort = newSerialPort;                //将新的串口序列存储起来
    }
}

mainMonitor::~mainMonitor()
{
    delete ui;
}

void mainMonitor::on_pushButton_abnormal_clicked()
{
    myAbnormal->show();
}


void mainMonitor::on_Button_Button_waterlevel_licked()
{

}


void mainMonitor::on_Button_temperature_clicked()
{
    systemData1.drawing_flag = 0;
    //line_flag=0;
//    /*创建所要绘制的二维图像的对象*/
    QChart* chart = new QChart();
    // 构建折线系列对象
    QLineSeries *series = new QLineSeries();
    //QVector<uchar> TemperatureData; //数据容器，温度
    for(int x = 0;x<systemData1.Temperature.size();x++)
    {
        //        TemperatureData[x]= x;
        series->append(x,systemData1.Temperature.at(x));    //压入数据
    }

    chart->resize(1800,1600);
    chart->addSeries(series);
    chart->createDefaultAxes();
    //    chart->setTitle("环境参数");
    series->setName("温度");
    chart->axes().at(0)->setTitleText("时间");    //一般X轴索引为0
    chart->axes().at(1)->setTitleText("温度");    //一般X轴索引为0
    series->setPen(pen_tempreature);
    ui->graphicsView->setChart(chart);
}


void mainMonitor::on_Button_waterlevel_clicked()
{
    systemData1.drawing_flag = 2;
    /*创建所要绘制的二维图像的对象*/
    QChart* chart = new QChart();
    // 构建折线系列对象
    QLineSeries *series = new QLineSeries();
    for(int x = 2;x<systemData1.Waterlevel.size();x++)
    {
        //        TemperatureData[x]= x;
        series->append(x,systemData1.Waterlevel.at(x));    //压入数据
    }

    chart->resize(1800,1600);
    chart->addSeries(series);
    chart->createDefaultAxes();
    //    chart->setTitle("环境参数");
    series->setName("水位");
    chart->axes().at(0)->setTitleText("时间");    //一般X轴索引为0
    chart->axes().at(1)->setTitleText("水位");    //一般X轴索引为0


    series->setPen(pen_waterlevel);
    ui->graphicsView->setChart(chart);
}


void mainMonitor::on_Button_wet_clicked()
{
    systemData1.drawing_flag = 1;
   // line_flag=1;
    /*创建所要绘制的二维图像的对象*/
    QChart* chart = new QChart();
//    //chart->legend()->setLabelColor(Qt::blue);
//    // 构建折线系列对象
    QLineSeries *series = new QLineSeries();
    QVector<uchar> TemperatureData; //数据容器，温度
    for(int x = 2;x<systemData1.Wet.size();x++)
    {
        //        TemperatureData[x]= x;
        series->append(x,systemData1.Wet.at(x));    //压入数据
    }

    chart->addSeries(series);
    chart->createDefaultAxes();
    series->setName("湿度");
    chart->axes().at(0)->setTitleText("时间");    //一般X轴索引为0
    chart->axes().at(1)->setTitleText("湿度");    //一般X轴索引为0


    series->setPen(pen_wet);
    ui->graphicsView->setChart(chart);
}

void mainMonitor::drawingline()
{
    QChart* chart = new QChart();
    //chart->legend()->setLabelColor(Qt::blue);
    // 构建折线系列对象
    QLineSeries *series = new QLineSeries();
    if(systemData1.drawing_flag==1)
    {

    }
    else if(systemData1.drawing_flag==2)
    {

    }
    else
    {

    }
    //if()
}

void mainMonitor::on_Button_start_clicked()
{
    int result = 0;
    result = my_tcpnet->connectServer();

    if(result == -1)
   {
         QMessageBox::information(this,QString::fromUtf8("TCP连接提示"),QString::fromUtf8("连接超时！"));
    }
    else if(result == 1)
    {
        tcp_start_flag = 1;
        QMessageBox::information(this,QString::fromUtf8("TCP连接提示"),QString::fromUtf8("连接成功！"));
        my_tcpnet->SendEnvir_Parameter();
        my_tcpnet->disconnectServer();
    }
}


void mainMonitor::on_Button_sendPicture_clicked()
{
    int result = 0;
    //result = my_tcpnet->connectServer();
    if(result == -1)
    {
        QMessageBox::information(this,QString::fromUtf8("TCP连接提示"),QString::fromUtf8("连接超时！"));
    }
    else if(result == 1)
    {
        my_tcpnet->SendPicture();//向服务器发送图片数据
        //my_tcpnet->disconnectServer();
        //my_tcpnet->SendEnvir_Parameter();
    }
}


void mainMonitor::on_Button_ph_clicked()
{
    systemData1.drawing_flag = 3;
    /*创建所要绘制的二维图像的对象*/
    QChart* chart = new QChart();
    // 构建折线系列对象
    QLineSeries *series = new QLineSeries();
    for(int x = 2;x<systemData1.PH.size();x++)
    {
        //        TemperatureData[x]= x;
        series->append(x,systemData1.PH.at(x));    //压入数据
    }

    chart->resize(1800,1600);
    chart->addSeries(series);
    chart->createDefaultAxes();
    //    chart->setTitle("环境参数");
    series->setName("PH");
    chart->axes().at(0)->setTitleText("时间");    //一般X轴索引为0
    chart->axes().at(1)->setTitleText("PH");    //一般X轴索引为0


    series->setPen(pen_waterlevel);
    ui->graphicsView->setChart(chart);
    //myPH_page->show();
}

