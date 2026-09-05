#include "set_help.h"
#include "ui_set_help.h"

set_help::set_help(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::set_help)
{
    ui->setupUi(this);
    this->setWindowTitle("help");
}

set_help::~set_help()
{
    delete ui;
}
