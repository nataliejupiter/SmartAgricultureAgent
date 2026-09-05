#ifndef TEMPERTURE_PAGE_H
#define TEMPERTURE_PAGE_H

#include <QWidget>
#include"set_help.h"
#include <QTimer>
//#include "welcome.h"
namespace Ui {
class temperture_page;
}

class temperture_page : public QWidget
{
    Q_OBJECT

public:
    explicit temperture_page(QWidget *parent = nullptr);
    ~temperture_page();
    void data_read();
    set_help *set_helpPage = NULL;      //设置帮助界面
    float T_limit[2];  //温度限制数据，第0个数为上线，第一个数为下限，下面的数据也相同

private slots:
    void on_help_clicked();

    void on_help_2_clicked();

    void on_help_3_clicked();

    void on_help_5_clicked();

    void on_help_4_clicked();

    void on_selfSet_clicked();

    void on_AutoSet_clicked();

private:
    Ui::temperture_page *ui;
};

#endif // TEMPERTURE_PAGE_H
