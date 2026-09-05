/********************************************************************************
** Form generated from reading UI file 'mainmonitor.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINMONITOR_H
#define UI_MAINMONITOR_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainMonitor
{
public:
    QLabel *camera;
    QLabel *label_temperature;
    QLineEdit *lineEdit_temperature;
    QLineEdit *lineEdit_wet;
    QLabel *label_wet;
    QLineEdit *lineEdit_waterlevel;
    QLabel *label_waterlevel;
    QPushButton *Button_temperature;
    QPushButton *Button_wet;
    QPushButton *Button_waterlevel;
    QPushButton *Button_sendPicture;
    QPushButton *Button_start;
    QChartView *graphicsView;
    QPushButton *pushButton_abnormal;
    QLabel *label;
    QLabel *sum;
    QLabel *label_ph;
    QLineEdit *lineEdit_ph;
    QPushButton *Button_ph;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QWidget *mainMonitor)
    {
        if (mainMonitor->objectName().isEmpty())
            mainMonitor->setObjectName("mainMonitor");
        mainMonitor->resize(915, 493);
        camera = new QLabel(mainMonitor);
        camera->setObjectName("camera");
        camera->setGeometry(QRect(20, 40, 211, 181));
        camera->setStyleSheet(QString::fromUtf8("rgb (152, 152, 152);"));
        label_temperature = new QLabel(mainMonitor);
        label_temperature->setObjectName("label_temperature");
        label_temperature->setGeometry(QRect(360, 40, 31, 16));
        lineEdit_temperature = new QLineEdit(mainMonitor);
        lineEdit_temperature->setObjectName("lineEdit_temperature");
        lineEdit_temperature->setGeometry(QRect(400, 40, 113, 23));
        lineEdit_wet = new QLineEdit(mainMonitor);
        lineEdit_wet->setObjectName("lineEdit_wet");
        lineEdit_wet->setGeometry(QRect(400, 70, 113, 23));
        label_wet = new QLabel(mainMonitor);
        label_wet->setObjectName("label_wet");
        label_wet->setGeometry(QRect(360, 70, 31, 16));
        lineEdit_waterlevel = new QLineEdit(mainMonitor);
        lineEdit_waterlevel->setObjectName("lineEdit_waterlevel");
        lineEdit_waterlevel->setGeometry(QRect(400, 100, 113, 23));
        label_waterlevel = new QLabel(mainMonitor);
        label_waterlevel->setObjectName("label_waterlevel");
        label_waterlevel->setGeometry(QRect(360, 100, 31, 16));
        Button_temperature = new QPushButton(mainMonitor);
        Button_temperature->setObjectName("Button_temperature");
        Button_temperature->setGeometry(QRect(310, 160, 51, 51));
        Button_wet = new QPushButton(mainMonitor);
        Button_wet->setObjectName("Button_wet");
        Button_wet->setGeometry(QRect(380, 160, 51, 51));
        Button_waterlevel = new QPushButton(mainMonitor);
        Button_waterlevel->setObjectName("Button_waterlevel");
        Button_waterlevel->setGeometry(QRect(450, 160, 51, 51));
        Button_sendPicture = new QPushButton(mainMonitor);
        Button_sendPicture->setObjectName("Button_sendPicture");
        Button_sendPicture->setGeometry(QRect(240, 50, 61, 51));
        Button_start = new QPushButton(mainMonitor);
        Button_start->setObjectName("Button_start");
        Button_start->setGeometry(QRect(240, 120, 61, 51));
        graphicsView = new QChartView(mainMonitor);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(10, 230, 491, 231));
        pushButton_abnormal = new QPushButton(mainMonitor);
        pushButton_abnormal->setObjectName("pushButton_abnormal");
        pushButton_abnormal->setGeometry(QRect(510, 360, 80, 81));
        label = new QLabel(mainMonitor);
        label->setObjectName("label");
        label->setGeometry(QRect(510, 240, 54, 31));
        sum = new QLabel(mainMonitor);
        sum->setObjectName("sum");
        sum->setGeometry(QRect(520, 290, 54, 31));
        label_ph = new QLabel(mainMonitor);
        label_ph->setObjectName("label_ph");
        label_ph->setGeometry(QRect(360, 130, 31, 16));
        lineEdit_ph = new QLineEdit(mainMonitor);
        lineEdit_ph->setObjectName("lineEdit_ph");
        lineEdit_ph->setGeometry(QRect(400, 130, 113, 23));
        Button_ph = new QPushButton(mainMonitor);
        Button_ph->setObjectName("Button_ph");
        Button_ph->setGeometry(QRect(520, 160, 51, 51));
        label_2 = new QLabel(mainMonitor);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(520, 40, 68, 22));
        label_3 = new QLabel(mainMonitor);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(520, 70, 68, 22));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        label_3->setFont(font);
        label_4 = new QLabel(mainMonitor);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(520, 100, 68, 22));

        retranslateUi(mainMonitor);

        QMetaObject::connectSlotsByName(mainMonitor);
    } // setupUi

    void retranslateUi(QWidget *mainMonitor)
    {
        mainMonitor->setWindowTitle(QCoreApplication::translate("mainMonitor", "Form", nullptr));
        camera->setText(QCoreApplication::translate("mainMonitor", "<html><head/><body><p align=\"center\">camera</p></body></html>", nullptr));
        label_temperature->setText(QCoreApplication::translate("mainMonitor", "\346\270\251\345\272\246\357\274\232", nullptr));
        label_wet->setText(QCoreApplication::translate("mainMonitor", "\346\271\277\345\272\246\357\274\232", nullptr));
        lineEdit_waterlevel->setText(QString());
        label_waterlevel->setText(QCoreApplication::translate("mainMonitor", "\346\260\264\344\275\215\357\274\232", nullptr));
        Button_temperature->setText(QCoreApplication::translate("mainMonitor", "\346\270\251\345\272\246", nullptr));
        Button_wet->setText(QCoreApplication::translate("mainMonitor", "\346\271\277\345\272\246", nullptr));
        Button_waterlevel->setText(QCoreApplication::translate("mainMonitor", "\346\260\264\344\275\215", nullptr));
        Button_sendPicture->setText(QCoreApplication::translate("mainMonitor", "\347\253\213\345\215\263\345\217\221\351\200\201", nullptr));
        Button_start->setText(QCoreApplication::translate("mainMonitor", "\345\220\257\345\212\250", nullptr));
        pushButton_abnormal->setText(QCoreApplication::translate("mainMonitor", "\345\274\202\345\270\270\346\266\210\346\201\257\345\244\204\347\220\206", nullptr));
        label->setText(QCoreApplication::translate("mainMonitor", "\345\274\202\345\270\270\346\225\260\351\207\217\357\274\232", nullptr));
        sum->setText(QCoreApplication::translate("mainMonitor", "<html><head/><body><p align=\"center\">0</p></body></html>", nullptr));
        label_ph->setText(QCoreApplication::translate("mainMonitor", "ph", nullptr));
        lineEdit_ph->setText(QString());
        Button_ph->setText(QCoreApplication::translate("mainMonitor", "ph", nullptr));
        label_2->setText(QCoreApplication::translate("mainMonitor", "\342\204\203", nullptr));
        label_3->setText(QCoreApplication::translate("mainMonitor", "%", nullptr));
        label_4->setText(QCoreApplication::translate("mainMonitor", "cm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainMonitor: public Ui_mainMonitor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINMONITOR_H
