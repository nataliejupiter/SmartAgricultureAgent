#ifndef WATERLEVEL_PAGE_H
#define WATERLEVEL_PAGE_H

#include <QWidget>

namespace Ui {
class waterlevel_page;
}

class waterlevel_page : public QWidget
{
    Q_OBJECT

public:
    explicit waterlevel_page(QWidget *parent = nullptr);
    ~waterlevel_page();
    void data_read();
private slots:
    void on_help_2_clicked();

    void on_help_3_clicked();

    void on_help_5_clicked();

    void on_help_4_clicked();

private:
    Ui::waterlevel_page *ui;
};

#endif // WATERLEVEL_PAGE_H
