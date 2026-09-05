#ifndef PH_PAGE_H
#define PH_PAGE_H

#include <QWidget>
#include"set_help.h"
namespace Ui {
class PH_page;
}

class PH_page : public QWidget
{
    Q_OBJECT

public:
    explicit PH_page(QWidget *parent = nullptr);
    ~PH_page();
    set_help *set_helpPage = NULL;      //设置帮助界面
    void data_read();
private slots:
    void on_pushButton_clicked();

    void on_help_2_clicked();

    void on_help_3_clicked();

    void on_help_5_clicked();

    void on_help_4_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::PH_page *ui;
};

#endif // PH_PAGE_H
