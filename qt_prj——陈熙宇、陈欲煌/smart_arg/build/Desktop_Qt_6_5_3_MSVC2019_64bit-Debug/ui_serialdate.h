/********************************************************************************
** Form generated from reading UI file 'serialdate.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIALDATE_H
#define UI_SERIALDATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_serialdate
{
public:
    QPlainTextEdit *plainTextEdit;
    QPushButton *pushButton_clear;
    QLabel *label;
    QRadioButton *radioButton_Hex;
    QRadioButton *radioButton_Dec;

    void setupUi(QWidget *serialdate)
    {
        if (serialdate->objectName().isEmpty())
            serialdate->setObjectName("serialdate");
        serialdate->resize(428, 322);
        plainTextEdit = new QPlainTextEdit(serialdate);
        plainTextEdit->setObjectName("plainTextEdit");
        plainTextEdit->setGeometry(QRect(10, 20, 351, 231));
        pushButton_clear = new QPushButton(serialdate);
        pushButton_clear->setObjectName("pushButton_clear");
        pushButton_clear->setGeometry(QRect(270, 260, 101, 31));
        label = new QLabel(serialdate);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 0, 54, 16));
        radioButton_Hex = new QRadioButton(serialdate);
        radioButton_Hex->setObjectName("radioButton_Hex");
        radioButton_Hex->setGeometry(QRect(90, 0, 71, 22));
        radioButton_Dec = new QRadioButton(serialdate);
        radioButton_Dec->setObjectName("radioButton_Dec");
        radioButton_Dec->setGeometry(QRect(160, 0, 61, 22));

        retranslateUi(serialdate);

        QMetaObject::connectSlotsByName(serialdate);
    } // setupUi

    void retranslateUi(QWidget *serialdate)
    {
        serialdate->setWindowTitle(QCoreApplication::translate("serialdate", "Form", nullptr));
        pushButton_clear->setText(QCoreApplication::translate("serialdate", "\346\270\205\351\231\244", nullptr));
        label->setText(QCoreApplication::translate("serialdate", "\345\216\206\345\217\262\346\225\260\346\215\256\357\274\232", nullptr));
        radioButton_Hex->setText(QCoreApplication::translate("serialdate", "16\350\277\233\345\210\266", nullptr));
        radioButton_Dec->setText(QCoreApplication::translate("serialdate", "\345\215\201\350\277\233\345\210\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class serialdate: public Ui_serialdate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALDATE_H
