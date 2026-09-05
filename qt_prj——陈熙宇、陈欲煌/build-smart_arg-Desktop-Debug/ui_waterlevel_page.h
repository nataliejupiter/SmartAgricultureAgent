/********************************************************************************
** Form generated from reading UI file 'waterlevel_page.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WATERLEVEL_PAGE_H
#define UI_WATERLEVEL_PAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_waterlevel_page
{
public:
    QLineEdit *HIGHlevel;
    QLineEdit *lowlevel;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;
    QPushButton *help_3;
    QPushButton *help_2;
    QPushButton *help_5;
    QPushButton *help_4;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QWidget *waterlevel_page)
    {
        if (waterlevel_page->objectName().isEmpty())
            waterlevel_page->setObjectName("waterlevel_page");
        waterlevel_page->resize(300, 200);
        waterlevel_page->setMinimumSize(QSize(300, 200));
        waterlevel_page->setMaximumSize(QSize(300, 200));
        HIGHlevel = new QLineEdit(waterlevel_page);
        HIGHlevel->setObjectName("HIGHlevel");
        HIGHlevel->setGeometry(QRect(80, 30, 81, 27));
        lowlevel = new QLineEdit(waterlevel_page);
        lowlevel->setObjectName("lowlevel");
        lowlevel->setGeometry(QRect(80, 70, 81, 27));
        label = new QLabel(waterlevel_page);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 30, 69, 19));
        label_2 = new QLabel(waterlevel_page);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 70, 69, 19));
        pushButton = new QPushButton(waterlevel_page);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(200, 120, 61, 51));
        help_3 = new QPushButton(waterlevel_page);
        help_3->setObjectName("help_3");
        help_3->setGeometry(QRect(241, 20, 41, 41));
        help_2 = new QPushButton(waterlevel_page);
        help_2->setObjectName("help_2");
        help_2->setGeometry(QRect(202, 20, 41, 41));
        help_5 = new QPushButton(waterlevel_page);
        help_5->setObjectName("help_5");
        help_5->setGeometry(QRect(201, 60, 41, 41));
        help_4 = new QPushButton(waterlevel_page);
        help_4->setObjectName("help_4");
        help_4->setGeometry(QRect(240, 60, 41, 41));
        label_3 = new QLabel(waterlevel_page);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(170, 30, 31, 19));
        label_4 = new QLabel(waterlevel_page);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(170, 70, 31, 19));

        retranslateUi(waterlevel_page);

        QMetaObject::connectSlotsByName(waterlevel_page);
    } // setupUi

    void retranslateUi(QWidget *waterlevel_page)
    {
        waterlevel_page->setWindowTitle(QCoreApplication::translate("waterlevel_page", "Form", nullptr));
        HIGHlevel->setText(QCoreApplication::translate("waterlevel_page", "20.0", nullptr));
        lowlevel->setText(QCoreApplication::translate("waterlevel_page", "2.0", nullptr));
        label->setText(QCoreApplication::translate("waterlevel_page", "\344\270\212\351\231\220\346\260\264\344\275\215", nullptr));
        label_2->setText(QCoreApplication::translate("waterlevel_page", "\344\270\213\351\231\220\346\260\264\344\275\215", nullptr));
        pushButton->setText(QCoreApplication::translate("waterlevel_page", "\350\256\276\347\275\256", nullptr));
        help_3->setText(QCoreApplication::translate("waterlevel_page", "-", nullptr));
        help_2->setText(QCoreApplication::translate("waterlevel_page", "+", nullptr));
        help_5->setText(QCoreApplication::translate("waterlevel_page", "+", nullptr));
        help_4->setText(QCoreApplication::translate("waterlevel_page", "-", nullptr));
        label_3->setText(QCoreApplication::translate("waterlevel_page", "cm", nullptr));
        label_4->setText(QCoreApplication::translate("waterlevel_page", "cm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class waterlevel_page: public Ui_waterlevel_page {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WATERLEVEL_PAGE_H
