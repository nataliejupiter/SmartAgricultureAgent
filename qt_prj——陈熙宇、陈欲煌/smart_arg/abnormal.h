#ifndef ABNORMAL_H
#define ABNORMAL_H

#include <QWidget>
/*绘图相关*/
#include "QtCharts/QChartView"
#include "QtCharts/QPieSlice"
#include <QtCharts/QValueAxis>
#include <QtCharts>
#include <QTimer>
namespace Ui {
class abnormal;
}

class abnormal : public QWidget
{
    Q_OBJECT

public:
    explicit abnormal(QWidget *parent = nullptr);
    ~abnormal();
    QPieSeries *pie_series;
    QChart *mChart;
    QTimer *SerialTimer=NULL;
private slots:
    void updatePieChart();
private:
    Ui::abnormal *ui;
    QTimer *timer;

};

#endif // ABNORMAL_H
