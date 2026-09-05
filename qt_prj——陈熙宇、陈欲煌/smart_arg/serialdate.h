#ifndef SERIALDATE_H
#define SERIALDATE_H

#include <QWidget>

namespace Ui {
class serialdate;
}

class serialdate : public QWidget
{
    Q_OBJECT

public:
    explicit serialdate(QWidget *parent = nullptr);
    ~serialdate();
    void push_data(QString);

private slots:
    void on_pushButton_clear_clicked();

    void on_radioButton_Hex_clicked();

private:
    Ui::serialdate *ui;
};

#endif // SERIALDATE_H
