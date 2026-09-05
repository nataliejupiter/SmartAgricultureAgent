#include "abnormal.h"
#include "mainmonitor.h"
#include "ui_abnormal.h"
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QTimer>
extern  systemData systemData1;
extern  situationSattus situationSattus1;
abnormal::abnormal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::abnormal)
{
    ui->setupUi(this);
    this->setWindowTitle("异常消息处理窗口");
    this->setFixedSize(500,380);

    pie_series = new QPieSeries(this);
    mChart = new QChart;

    // 初始化定时器
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &abnormal::updatePieChart);
    timer->start(1500);

    updatePieChart();

    mChart->setTheme(QChart::ChartThemeLight);
    mChart->setDropShadowEnabled(true);

    mChart->addSeries(pie_series);
    QChartView *chartView = new QChartView(mChart);
    ui->graphicsView->setChart(mChart);
}

abnormal::~abnormal()
{
    delete ui;
}

void abnormal::updatePieChart()
{
    // 清空之前的数据
    pie_series->clear();


    // 添加新的数据
    pie_series->append("温度异常", situationSattus1.temperature_promble_number);
    pie_series->append("湿度异常", situationSattus1.wet_promble_number);
    pie_series->append("PH异常", situationSattus1.ph_problem_number);
    pie_series->append("病虫害异常", situationSattus1.diseases_number);
    pie_series->append("水位异常", situationSattus1.water_pormble_number);
    pie_series->append("光照异常", situationSattus1.sunshine_problem_number);


    pie_series->setLabelsVisible(true);
    pie_series->setUseOpenGL(true);

    pie_series->slices().at(0)->setColor(QColor( 13,128,127));
    pie_series->slices().at(0)->setLabelColor(QColor(13,128,127));
    pie_series->slices().at(1)->setColor(QColor( 13,28,127));
    pie_series->slices().at(1)->setLabelColor(QColor(13,28,127));
    pie_series->slices().at(2)->setColor(QColor( 13,128,27));
    pie_series->slices().at(2)->setLabelColor(QColor(13,128,27));
    pie_series->slices().at(3)->setColor(QColor( 133,128,27));
    pie_series->slices().at(3)->setLabelColor(QColor(133,128,27));
    pie_series->slices().at(4)->setColor(QColor( 153,128,127));
    pie_series->slices().at(4)->setLabelColor(QColor(153,128,127));
    pie_series->slices().at(5)->setColor(QColor(233, 128, 27));
    pie_series->slices().at(5)->setLabelColor(QColor(233, 128, 27));
}
