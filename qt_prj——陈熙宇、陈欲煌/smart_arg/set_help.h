#ifndef SET_HELP_H
#define SET_HELP_H

#include <QWidget>

namespace Ui {
class set_help;
}

class set_help : public QWidget
{
    Q_OBJECT

public:
    explicit set_help(QWidget *parent = nullptr);
    ~set_help();

private:
    Ui::set_help *ui;
};

#endif // SET_HELP_H
