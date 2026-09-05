#ifndef WELCOME_H
#define WELCOME_H

#include <QWidget>
#include<QKeyEvent>
#include "mainmonitor.h"
#include "QTimer"
namespace Ui {
class welcome;
}

class welcome : public QWidget
{
    Q_OBJECT

public:
    explicit welcome(QWidget *parent = nullptr);
    ~welcome();
    mainMonitor *myMainMonitor = NULL;
    int enterflag = 0;
    void keyPressEvent(QKeyEvent *event);
    void welcome_loard();

private:
    Ui::welcome *ui;
    QTimer  *welcome_timer=NULL;
};

#endif // WELCOME_H
