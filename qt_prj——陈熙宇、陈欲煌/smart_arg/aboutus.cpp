#include "aboutus.h"
#include "ui_aboutus.h"

aboutus::aboutus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::aboutus)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:white;");
    this->setWindowTitle("关于我们");
    ui->label->setPixmap(QPixmap( ":jxust.jpg").scaled(ui->label->size(),
                                                             Qt::IgnoreAspectRatio,
                                                             Qt::SmoothTransformation));
}

aboutus::~aboutus()
{
    delete ui;
}
