#include "widget.h"
#include "mainwindow.h"
#include "welcome.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    welcome myWelcome;
    myWelcome.show();
    return a.exec();
}
