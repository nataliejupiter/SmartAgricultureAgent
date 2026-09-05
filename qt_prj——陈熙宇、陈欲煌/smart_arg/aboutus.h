#ifndef ABOUTUS_H
#define ABOUTUS_H

#include <QWidget>

namespace Ui {
class aboutus;
}

class aboutus : public QWidget
{
    Q_OBJECT

public:
    explicit aboutus(QWidget *parent = nullptr);
    ~aboutus();

private:
    Ui::aboutus *ui;
};

#endif // ABOUTUS_H
