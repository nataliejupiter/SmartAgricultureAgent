/********************************************************************************
** Form generated from reading UI file 'temperture_page.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEMPERTURE_PAGE_H
#define UI_TEMPERTURE_PAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_temperture_page
{
public:
    QLineEdit *HighEdit;
    QLabel *HighLimit;
    QLabel *LowLimit;
    QLineEdit *LowEdit;
    QLabel *label_T1;
    QLabel *label_T2;
    QLabel *auto_type;
    QComboBox *autoTypeList;
    QPushButton *AutoSet;
    QPushButton *selfSet;
    QPushButton *help;
    QPushButton *help_2;
    QPushButton *help_3;
    QPushButton *help_4;
    QPushButton *help_5;

    void setupUi(QWidget *temperture_page)
    {
        if (temperture_page->objectName().isEmpty())
            temperture_page->setObjectName("temperture_page");
        temperture_page->resize(300, 200);
        temperture_page->setMinimumSize(QSize(300, 200));
        temperture_page->setMaximumSize(QSize(300, 200));
        HighEdit = new QLineEdit(temperture_page);
        HighEdit->setObjectName("HighEdit");
        HighEdit->setGeometry(QRect(70, 60, 111, 23));
        HighLimit = new QLabel(temperture_page);
        HighLimit->setObjectName("HighLimit");
        HighLimit->setGeometry(QRect(10, 60, 53, 15));
        LowLimit = new QLabel(temperture_page);
        LowLimit->setObjectName("LowLimit");
        LowLimit->setGeometry(QRect(10, 90, 53, 15));
        LowEdit = new QLineEdit(temperture_page);
        LowEdit->setObjectName("LowEdit");
        LowEdit->setGeometry(QRect(70, 90, 111, 23));
        label_T1 = new QLabel(temperture_page);
        label_T1->setObjectName("label_T1");
        label_T1->setGeometry(QRect(190, 60, 21, 16));
        label_T2 = new QLabel(temperture_page);
        label_T2->setObjectName("label_T2");
        label_T2->setGeometry(QRect(190, 90, 21, 16));
        auto_type = new QLabel(temperture_page);
        auto_type->setObjectName("auto_type");
        auto_type->setGeometry(QRect(10, 30, 91, 20));
        autoTypeList = new QComboBox(temperture_page);
        autoTypeList->addItem(QString());
        autoTypeList->addItem(QString());
        autoTypeList->setObjectName("autoTypeList");
        autoTypeList->setGeometry(QRect(110, 22, 71, 31));
        AutoSet = new QPushButton(temperture_page);
        AutoSet->setObjectName("AutoSet");
        AutoSet->setGeometry(QRect(100, 130, 61, 51));
        selfSet = new QPushButton(temperture_page);
        selfSet->setObjectName("selfSet");
        selfSet->setGeometry(QRect(20, 130, 61, 51));
        help = new QPushButton(temperture_page);
        help->setObjectName("help");
        help->setGeometry(QRect(250, 160, 20, 21));
        help_2 = new QPushButton(temperture_page);
        help_2->setObjectName("help_2");
        help_2->setGeometry(QRect(211, 50, 41, 41));
        help_3 = new QPushButton(temperture_page);
        help_3->setObjectName("help_3");
        help_3->setGeometry(QRect(250, 50, 41, 41));
        help_4 = new QPushButton(temperture_page);
        help_4->setObjectName("help_4");
        help_4->setGeometry(QRect(249, 90, 41, 41));
        help_5 = new QPushButton(temperture_page);
        help_5->setObjectName("help_5");
        help_5->setGeometry(QRect(210, 90, 41, 41));

        retranslateUi(temperture_page);

        QMetaObject::connectSlotsByName(temperture_page);
    } // setupUi

    void retranslateUi(QWidget *temperture_page)
    {
        temperture_page->setWindowTitle(QCoreApplication::translate("temperture_page", "Form", nullptr));
        HighEdit->setText(QCoreApplication::translate("temperture_page", "25.0", nullptr));
        HighLimit->setText(QCoreApplication::translate("temperture_page", "\344\270\212\351\231\220\346\270\251\345\272\246", nullptr));
        LowLimit->setText(QCoreApplication::translate("temperture_page", "\344\270\213\351\231\220\346\270\251\345\272\246", nullptr));
        LowEdit->setText(QCoreApplication::translate("temperture_page", "15.0", nullptr));
        label_T1->setText(QCoreApplication::translate("temperture_page", "\302\260C", nullptr));
        label_T2->setText(QCoreApplication::translate("temperture_page", "\302\260C", nullptr));
        auto_type->setText(QCoreApplication::translate("temperture_page", "\350\207\252\345\212\250\346\270\251\345\272\246\351\200\211\346\213\251", nullptr));
        autoTypeList->setItemText(0, QCoreApplication::translate("temperture_page", "\350\215\211\350\216\223", nullptr));
        autoTypeList->setItemText(1, QString());

        AutoSet->setText(QCoreApplication::translate("temperture_page", "\350\207\252\345\212\250\350\256\276\347\275\256", nullptr));
        selfSet->setText(QCoreApplication::translate("temperture_page", "\346\211\213\345\212\250\350\256\276\347\275\256", nullptr));
        help->setText(QCoreApplication::translate("temperture_page", "\357\274\237", nullptr));
        help_2->setText(QCoreApplication::translate("temperture_page", "+", nullptr));
        help_3->setText(QCoreApplication::translate("temperture_page", "-", nullptr));
        help_4->setText(QCoreApplication::translate("temperture_page", "-", nullptr));
        help_5->setText(QCoreApplication::translate("temperture_page", "+", nullptr));
    } // retranslateUi

};

namespace Ui {
    class temperture_page: public Ui_temperture_page {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEMPERTURE_PAGE_H
