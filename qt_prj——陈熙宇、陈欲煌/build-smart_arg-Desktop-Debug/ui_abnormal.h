/********************************************************************************
** Form generated from reading UI file 'abnormal.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABNORMAL_H
#define UI_ABNORMAL_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_abnormal
{
public:
    QChartView *graphicsView;

    void setupUi(QWidget *abnormal)
    {
        if (abnormal->objectName().isEmpty())
            abnormal->setObjectName("abnormal");
        abnormal->resize(584, 370);
        graphicsView = new QChartView(abnormal);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(10, 20, 371, 291));

        retranslateUi(abnormal);

        QMetaObject::connectSlotsByName(abnormal);
    } // setupUi

    void retranslateUi(QWidget *abnormal)
    {
        abnormal->setWindowTitle(QCoreApplication::translate("abnormal", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class abnormal: public Ui_abnormal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABNORMAL_H
