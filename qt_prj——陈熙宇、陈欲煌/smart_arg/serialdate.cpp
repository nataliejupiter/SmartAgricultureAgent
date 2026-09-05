#include "serialdate.h"
#include "ui_serialdate.h"

serialdate::serialdate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::serialdate)
{
    ui->setupUi(this);
    this->setWindowTitle("串口数据查看");
    this->setFixedSize(420,300);
    this->ui->radioButton_Hex->setChecked(1);
}

serialdate::~serialdate()
{
    delete ui;
}

void serialdate::push_data(QString data)
{
    ui->plainTextEdit->insertPlainText(data+'\n');//setPlainText(data);
}

void serialdate::on_pushButton_clear_clicked()
{
    ui->plainTextEdit->clear();
}


void serialdate::on_radioButton_Hex_clicked()
{
    //ui->plainTextEdit->toPlainText();
}

