#include "waterlevel_page.h"
#include "mainmonitor.h"
#include "ui_waterlevel_page.h"
extern systemData systemData1;
waterlevel_page::waterlevel_page(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::waterlevel_page)
{
    ui->setupUi(this);
    this->setWindowTitle("水位设置页面");
}

waterlevel_page::~waterlevel_page()
{
    delete ui;
}

void waterlevel_page::data_read()
{
    bool ok;

    systemData1.waterlevel_limit[0] = ui->HIGHlevel->text().toFloat(&ok);
    systemData1.waterlevel_limit[1] = ui->lowlevel->text().toFloat(&ok);
}
void waterlevel_page::on_help_2_clicked()
{
    float high=ui->HIGHlevel->text().toFloat();
    high=high+0.1;
    QString str_high = QString::number(high);
    ui->HIGHlevel->setText(str_high);
}


void waterlevel_page::on_help_3_clicked()
{
    float high=ui->HIGHlevel->text().toFloat();
    high=high-0.1;
    QString str_high = QString::number(high);
    ui->HIGHlevel->setText(str_high);
}


void waterlevel_page::on_help_5_clicked()
{
    float high=ui->lowlevel->text().toFloat();
    high=high+0.1;
    QString str_high = QString::number(high);
    ui->lowlevel->setText(str_high);
}


void waterlevel_page::on_help_4_clicked()
{
    float high=ui->lowlevel->text().toFloat();
    high=high-0.1;
    QString str_high = QString::number(high);
    ui->lowlevel->setText(str_high);
}

