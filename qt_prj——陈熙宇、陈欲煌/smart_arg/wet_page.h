#ifndef WET_PAGE_H
#define WET_PAGE_H

#include <QWidget>
#include"set_help.h"
namespace Ui {
class wet_page;
}

class wet_page : public QWidget
{
    Q_OBJECT

public:
    explicit wet_page(QWidget *parent = nullptr);
    ~wet_page();
    set_help *set_helpPage = NULL;      //设置帮助界面
    void data_read();
private slots:
    void on_pushButton_3_clicked();

    void on_high_limit_add_clicked();

    void on_high_limit_minus_clicked();

    void on_low_limit_add_clicked();

    void on_low_limit_minus_clicked();

private:
    Ui::wet_page *ui;
};

#endif // WET_PAGE_H
