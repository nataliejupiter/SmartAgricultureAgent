#include "wet_page.h"
#include "mainmonitor.h"
#include "ui_wet_page.h"
#include"set_help.h"
extern systemData systemData1;
wet_page::wet_page(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::wet_page)
{
    ui->setupUi(this);
    this->setWindowTitle("湿度设置");
    this->set_helpPage = new set_help;
}
void wet_page::data_read()
{
    bool ok;

    systemData1.wet_limit[0] = ui->highwet->text().toFloat(&ok);
    systemData1.wet_limit[1] = ui->lowwet->text().toFloat(&ok);
}
wet_page::~wet_page()
{
    delete ui;
}

void wet_page::on_pushButton_3_clicked()
{
    set_helpPage->show();
}


void wet_page::on_high_limit_add_clicked()
{
    float high=ui->highwet->text().toFloat();
    high=high+0.1;
    QString str_high = QString::number(high);
    ui->highwet->setText(str_high);
}


void wet_page::on_high_limit_minus_clicked()
{
    float high=ui->highwet->text().toFloat();
    high=high-0.1;
    QString str_high = QString::number(high);
    ui->highwet->setText(str_high);
}


void wet_page::on_low_limit_add_clicked()
{
    float low=ui->lowwet->text().toFloat();
    low=low+0.1;
    QString str_low = QString::number(low);
    ui->lowwet->setText(str_low);
}


void wet_page::on_low_limit_minus_clicked()
{
    float low=ui->lowwet->text().toFloat();
    low=low-0.1;
    QString str_low = QString::number(low);
    ui->lowwet->setText(str_low);
}

