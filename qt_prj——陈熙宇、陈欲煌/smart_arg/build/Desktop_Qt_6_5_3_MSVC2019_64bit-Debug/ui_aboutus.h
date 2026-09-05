/********************************************************************************
** Form generated from reading UI file 'aboutus.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTUS_H
#define UI_ABOUTUS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_aboutus
{
public:
    QLabel *label;
    QTextEdit *textEdit;

    void setupUi(QWidget *aboutus)
    {
        if (aboutus->objectName().isEmpty())
            aboutus->setObjectName("aboutus");
        aboutus->resize(327, 300);
        label = new QLabel(aboutus);
        label->setObjectName("label");
        label->setGeometry(QRect(123, 60, 74, 74));
        label->setMinimumSize(QSize(74, 74));
        label->setMaximumSize(QSize(74, 74));
        textEdit = new QTextEdit(aboutus);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(80, 160, 151, 81));

        retranslateUi(aboutus);

        QMetaObject::connectSlotsByName(aboutus);
    } // setupUi

    void retranslateUi(QWidget *aboutus)
    {
        aboutus->setWindowTitle(QCoreApplication::translate("aboutus", "Form", nullptr));
        label->setText(QString());
        textEdit->setHtml(QCoreApplication::translate("aboutus", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\345\234\260\345\235\200\357\274\232\346\261\237\350\245\277\347\234\201\350\265\243\345\267\236\345\270\202\350\265\243\345\267\236\347\273\217\345\274\200\345\214\272\345\256\242\345\256\266\345\244\247\351\201\2231958\345\217\267</p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\""
                        ">\351\202\256\347\274\226\357\274\232341000</p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">All Rights Reserved</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class aboutus: public Ui_aboutus {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTUS_H
