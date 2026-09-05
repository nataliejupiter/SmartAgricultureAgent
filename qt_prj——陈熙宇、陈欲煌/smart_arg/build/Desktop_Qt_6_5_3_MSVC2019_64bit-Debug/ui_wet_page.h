/********************************************************************************
** Form generated from reading UI file 'wet_page.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WET_PAGE_H
#define UI_WET_PAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wet_page
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *highwet;
    QLineEdit *lowwet;
    QComboBox *comboBox;
    QPushButton *auto_set;
    QPushButton *set_param;
    QPushButton *pushButton_3;
    QPushButton *high_limit_add;
    QPushButton *high_limit_minus;
    QPushButton *low_limit_minus;
    QPushButton *low_limit_add;

    void setupUi(QWidget *wet_page)
    {
        if (wet_page->objectName().isEmpty())
            wet_page->setObjectName("wet_page");
        wet_page->resize(300, 200);
        wet_page->setMinimumSize(QSize(300, 200));
        wet_page->setMaximumSize(QSize(300, 200));
        label = new QLabel(wet_page);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 50, 69, 19));
        label_2 = new QLabel(wet_page);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 90, 69, 19));
        label_3 = new QLabel(wet_page);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(40, 10, 91, 20));
        highwet = new QLineEdit(wet_page);
        highwet->setObjectName("highwet");
        highwet->setGeometry(QRect(110, 50, 101, 27));
        lowwet = new QLineEdit(wet_page);
        lowwet->setObjectName("lowwet");
        lowwet->setGeometry(QRect(110, 90, 101, 27));
        comboBox = new QComboBox(wet_page);
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(140, 10, 89, 27));
        auto_set = new QPushButton(wet_page);
        auto_set->setObjectName("auto_set");
        auto_set->setGeometry(QRect(140, 130, 61, 51));
        set_param = new QPushButton(wet_page);
        set_param->setObjectName("set_param");
        set_param->setGeometry(QRect(50, 130, 61, 51));
        pushButton_3 = new QPushButton(wet_page);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(260, 160, 21, 21));
        high_limit_add = new QPushButton(wet_page);
        high_limit_add->setObjectName("high_limit_add");
        high_limit_add->setGeometry(QRect(220, 50, 31, 31));
        high_limit_minus = new QPushButton(wet_page);
        high_limit_minus->setObjectName("high_limit_minus");
        high_limit_minus->setGeometry(QRect(260, 50, 31, 31));
        low_limit_minus = new QPushButton(wet_page);
        low_limit_minus->setObjectName("low_limit_minus");
        low_limit_minus->setGeometry(QRect(260, 90, 31, 31));
        low_limit_add = new QPushButton(wet_page);
        low_limit_add->setObjectName("low_limit_add");
        low_limit_add->setGeometry(QRect(220, 90, 31, 31));

        retranslateUi(wet_page);

        QMetaObject::connectSlotsByName(wet_page);
    } // setupUi

    void retranslateUi(QWidget *wet_page)
    {
        wet_page->setWindowTitle(QCoreApplication::translate("wet_page", "Form", nullptr));
        label->setText(QCoreApplication::translate("wet_page", "\346\271\277\345\272\246\344\270\212\351\231\220", nullptr));
        label_2->setText(QCoreApplication::translate("wet_page", "\346\271\277\345\272\246\344\270\213\351\231\220", nullptr));
        label_3->setText(QCoreApplication::translate("wet_page", "\350\207\252\345\212\250\350\256\276\347\275\256\346\271\277\345\272\246", nullptr));
        highwet->setText(QCoreApplication::translate("wet_page", "80.0", nullptr));
        lowwet->setText(QCoreApplication::translate("wet_page", "60.0", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("wet_page", "\350\215\211\350\216\223", nullptr));

        auto_set->setText(QCoreApplication::translate("wet_page", "\350\207\252\345\212\250\350\256\276\347\275\256", nullptr));
        set_param->setText(QCoreApplication::translate("wet_page", "\346\211\213\345\212\250\350\256\276\347\275\256", nullptr));
        pushButton_3->setText(QCoreApplication::translate("wet_page", "?", nullptr));
        high_limit_add->setText(QCoreApplication::translate("wet_page", "+", nullptr));
        high_limit_minus->setText(QCoreApplication::translate("wet_page", "-", nullptr));
        low_limit_minus->setText(QCoreApplication::translate("wet_page", "-", nullptr));
        low_limit_add->setText(QCoreApplication::translate("wet_page", "+", nullptr));
    } // retranslateUi

};

namespace Ui {
    class wet_page: public Ui_wet_page {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WET_PAGE_H
