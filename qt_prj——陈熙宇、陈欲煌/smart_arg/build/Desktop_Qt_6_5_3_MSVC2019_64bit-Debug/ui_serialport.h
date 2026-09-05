/********************************************************************************
** Form generated from reading UI file 'serialport.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIALPORT_H
#define UI_SERIALPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_serialPort
{
public:
    QLabel *label_COM;
    QLabel *label_Baudrate;
    QLabel *label_stopBit;
    QLabel *label_calibrate;
    QLabel *label_flowcontral;
    QLabel *label_datebit;
    QComboBox *serialList;
    QComboBox *boundrate;
    QComboBox *stopbit;
    QComboBox *calibrate;
    QComboBox *flowcontral;
    QComboBox *datebit;

    void setupUi(QWidget *serialPort)
    {
        if (serialPort->objectName().isEmpty())
            serialPort->setObjectName("serialPort");
        serialPort->resize(796, 506);
        label_COM = new QLabel(serialPort);
        label_COM->setObjectName("label_COM");
        label_COM->setGeometry(QRect(20, 20, 41, 31));
        label_Baudrate = new QLabel(serialPort);
        label_Baudrate->setObjectName("label_Baudrate");
        label_Baudrate->setGeometry(QRect(20, 50, 41, 31));
        label_stopBit = new QLabel(serialPort);
        label_stopBit->setObjectName("label_stopBit");
        label_stopBit->setGeometry(QRect(20, 80, 41, 31));
        label_calibrate = new QLabel(serialPort);
        label_calibrate->setObjectName("label_calibrate");
        label_calibrate->setGeometry(QRect(170, 80, 41, 31));
        label_flowcontral = new QLabel(serialPort);
        label_flowcontral->setObjectName("label_flowcontral");
        label_flowcontral->setGeometry(QRect(170, 20, 41, 31));
        label_datebit = new QLabel(serialPort);
        label_datebit->setObjectName("label_datebit");
        label_datebit->setGeometry(QRect(170, 50, 41, 31));
        serialList = new QComboBox(serialPort);
        serialList->setObjectName("serialList");
        serialList->setGeometry(QRect(70, 20, 72, 24));
        boundrate = new QComboBox(serialPort);
        boundrate->addItem(QString());
        boundrate->addItem(QString());
        boundrate->addItem(QString());
        boundrate->addItem(QString());
        boundrate->setObjectName("boundrate");
        boundrate->setGeometry(QRect(70, 50, 72, 24));
        stopbit = new QComboBox(serialPort);
        stopbit->addItem(QString());
        stopbit->addItem(QString());
        stopbit->setObjectName("stopbit");
        stopbit->setGeometry(QRect(70, 80, 72, 24));
        calibrate = new QComboBox(serialPort);
        calibrate->addItem(QString());
        calibrate->addItem(QString());
        calibrate->addItem(QString());
        calibrate->setObjectName("calibrate");
        calibrate->setGeometry(QRect(220, 80, 72, 24));
        flowcontral = new QComboBox(serialPort);
        flowcontral->addItem(QString());
        flowcontral->addItem(QString());
        flowcontral->addItem(QString());
        flowcontral->setObjectName("flowcontral");
        flowcontral->setGeometry(QRect(220, 20, 72, 24));
        datebit = new QComboBox(serialPort);
        datebit->addItem(QString());
        datebit->addItem(QString());
        datebit->setObjectName("datebit");
        datebit->setGeometry(QRect(220, 50, 72, 24));

        retranslateUi(serialPort);

        QMetaObject::connectSlotsByName(serialPort);
    } // setupUi

    void retranslateUi(QWidget *serialPort)
    {
        serialPort->setWindowTitle(QCoreApplication::translate("serialPort", "Form", nullptr));
        label_COM->setText(QCoreApplication::translate("serialPort", "COM\357\274\232", nullptr));
        label_Baudrate->setText(QCoreApplication::translate("serialPort", "\346\263\242\347\211\271\347\216\207\357\274\232", nullptr));
        label_stopBit->setText(QCoreApplication::translate("serialPort", "\345\201\234\346\255\242\344\275\215\357\274\232", nullptr));
        label_calibrate->setText(QCoreApplication::translate("serialPort", "\346\240\241\351\252\214\344\275\215\357\274\232", nullptr));
        label_flowcontral->setText(QCoreApplication::translate("serialPort", "\346\265\201\346\216\247\357\274\232", nullptr));
        label_datebit->setText(QCoreApplication::translate("serialPort", "\346\225\260\346\215\256\344\275\215\357\274\232", nullptr));
        boundrate->setItemText(0, QCoreApplication::translate("serialPort", "9600", nullptr));
        boundrate->setItemText(1, QCoreApplication::translate("serialPort", "19200", nullptr));
        boundrate->setItemText(2, QCoreApplication::translate("serialPort", "38400", nullptr));
        boundrate->setItemText(3, QCoreApplication::translate("serialPort", "115200", nullptr));

        stopbit->setItemText(0, QCoreApplication::translate("serialPort", "1", nullptr));
        stopbit->setItemText(1, QCoreApplication::translate("serialPort", "1.5", nullptr));

        calibrate->setItemText(0, QCoreApplication::translate("serialPort", "None", nullptr));
        calibrate->setItemText(1, QCoreApplication::translate("serialPort", "odd", nullptr));
        calibrate->setItemText(2, QCoreApplication::translate("serialPort", "even", nullptr));

        flowcontral->setItemText(0, QCoreApplication::translate("serialPort", "None", nullptr));
        flowcontral->setItemText(1, QCoreApplication::translate("serialPort", "software", nullptr));
        flowcontral->setItemText(2, QCoreApplication::translate("serialPort", "hardware", nullptr));

        datebit->setItemText(0, QCoreApplication::translate("serialPort", "8", nullptr));
        datebit->setItemText(1, QCoreApplication::translate("serialPort", "9", nullptr));

    } // retranslateUi

};

namespace Ui {
    class serialPort: public Ui_serialPort {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALPORT_H
