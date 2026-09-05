#include "ph_page.h"
#include "mainmonitor.h"
#include "ui_ph_page.h"
extern systemData systemData1;
PH_page::PH_page(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PH_page)
{
    ui->setupUi(this);
    this->setWindowTitle("PH设置页面");
    this->set_helpPage = new set_help;
}


void PH_page::data_read()
{
    bool ok;

    // systemData1.wet_limit[0] = ui->HIGHlevel->text().toFloat(&ok);
    // systemData1.waterlevel_limit[1] = ui->lowlevel->text().toFloat(&ok);
}
PH_page::~PH_page()
{
    delete ui;
}

void PH_page::on_pushButton_clicked()
{
    set_helpPage->show();
}


void PH_page::on_help_2_clicked()
{
    float high=ui->highPH->text().toFloat();
    high=high+0.01;
    QString str_high = QString::number(high);
    ui->highPH->setText(str_high);
}


void PH_page::on_help_3_clicked()
{
    float high=ui->highPH->text().toFloat();
    high=high-0.01;
    QString str_high = QString::number(high);
    ui->highPH->setText(str_high);
}


void PH_page::on_help_5_clicked()
{
    float low=ui->lowPH->text().toFloat();
    low=low+0.01;
    QString str_high = QString::number(low);
    ui->lowPH->setText(str_high);
}


void PH_page::on_help_4_clicked()
{
    float low=ui->lowPH->text().toFloat();
    low=low-0.01;
    QString str_high = QString::number(low);
    ui->lowPH->setText(str_high);
}


void PH_page::on_pushButton_3_clicked()
{
    set_helpPage->show();
}

