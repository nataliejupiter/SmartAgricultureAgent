#include "welcome.h"
#include "ui_welcome.h"


welcome::welcome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::welcome)
{
    ui->setupUi(this);
    this->myMainMonitor=new mainMonitor;

    this->setFixedSize(600,480);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
                     QBrush(QPixmap(":background.jpg").scaled(    // 缩放背景图.        //green-1757807_1280    :/Image/ice-1502735_1280.jpg    C:/Users/cxy/Desktop/物理实验竞赛/ice-1502735_1280.jpg
                         this->size(),
                         Qt::IgnoreAspectRatio,
                         Qt::SmoothTransformation)));    // 使用平滑的缩放方式
    this->setPalette(palette);
    setWindowOpacity(0.9); //设置widget窗体透明度
    setWindowTitle("欢迎");


    welcome_timer = new QTimer;
    welcome_timer->start(2000);
    connect(welcome_timer,&QTimer::timeout,this,&welcome::welcome_loard);
}

welcome::~welcome()
{
    delete ui;
}

void welcome::welcome_loard()
{
   myMainMonitor->show();
   this->close();
   delete welcome_timer;
}

void welcome::keyPressEvent(QKeyEvent *event)
{
    if(enterflag == 0)
    {
        if(event->key() )
        {
            //myMainMonitor->show();
            this->close();            //关闭页面在后，防止页面被藏入后台

        }
        enterflag=1;
    }
}
