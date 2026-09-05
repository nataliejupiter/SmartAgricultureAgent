#include "temperture_page.h"
#include "mainmonitor.h"
#include "ui_temperture_page.h"
#include "welcome.h"
extern systemData systemData1;
extern plants struberry;
// QTimer *WetTimer = NULL;
// QTimer *WaterlevelTimer = NULL;
temperture_page::temperture_page(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::temperture_page)
{
    ui->setupUi(this);
    this->setWindowTitle("温度设置");
    this->set_helpPage = new set_help;
    //myMainMonitor
    //connect(TemperatureTimer,&QTimer::timeout,this, Temper_page->data_reflesh);    //创建
    //this->setWindowTitle("帮助");
}

temperture_page::~temperture_page()
{
    delete ui;
}
void temperture_page::data_read()
{
    bool ok;

    systemData1.terperature_limit[0] = ui->HighEdit->text().toFloat(&ok);
    systemData1.terperature_limit[1] = ui->LowEdit->text().toFloat(&ok);
}

void temperture_page::on_help_clicked()
{
    set_helpPage->show();
}


void temperture_page::on_help_2_clicked()
{
   //;
     float high=ui->HighEdit->text().toFloat();
   high=high+0.1;
     QString str_high = QString::number(high);
   ui->HighEdit->setText(str_high);
}


void temperture_page::on_help_3_clicked()
{
    float high=ui->HighEdit->text().toFloat();
    high=high-0.1;
    QString str_high = QString::number(high);
    ui->HighEdit->setText(str_high);
    // float low=ui->LowEdit->text().toFloat();
    // low=low+0.1;
    // QString str_high = QString::number(low);
    // ui->LowEdit->setText(str_high);
}


void temperture_page::on_help_5_clicked()
{
    float low=ui->LowEdit->text().toFloat();
    low=low+0.1;
    QString str_high = QString::number(low);
    ui->LowEdit->setText(str_high);
}


void temperture_page::on_help_4_clicked()
{

    float low=ui->LowEdit->text().toFloat();
    low=low-0.1;
    QString str_high = QString::number(low);
    ui->LowEdit->setText(str_high);
}


void temperture_page::on_selfSet_clicked()
{
    QMessageBox::information(this,QString::fromUtf8("提示"),QString::fromUtf8("温度区间设置成功！"));
}


void temperture_page::on_AutoSet_clicked()
{
    int typeSerial = 0;
    struberry.temperature[0];
    typeSerial = ui->autoTypeList->currentIndex();
    switch (typeSerial)
    {
        case 0:break;
        case 1:break;
        default:typeSerial = -1;break;
    }
        if(typeSerial == -1)
    {
        QMessageBox::information(this,QString::fromUtf8("提示"),QString::fromUtf8("自动设置出错！请检查设置！"));
            return;
    }
    QMessageBox::information(this,QString::fromUtf8("提示"),QString::fromUtf8("自动设置成功！"));
}

