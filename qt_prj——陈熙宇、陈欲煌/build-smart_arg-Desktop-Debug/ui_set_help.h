/********************************************************************************
** Form generated from reading UI file 'set_help.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SET_HELP_H
#define UI_SET_HELP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_set_help
{
public:
    QTextEdit *textEdit;

    void setupUi(QWidget *set_help)
    {
        if (set_help->objectName().isEmpty())
            set_help->setObjectName("set_help");
        set_help->resize(300, 200);
        set_help->setMinimumSize(QSize(300, 200));
        set_help->setMaximumSize(QSize(300, 200));
        textEdit = new QTextEdit(set_help);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(0, 10, 291, 181));

        retranslateUi(set_help);

        QMetaObject::connectSlotsByName(set_help);
    } // setupUi

    void retranslateUi(QWidget *set_help)
    {
        set_help->setWindowTitle(QCoreApplication::translate("set_help", "Form", nullptr));
        textEdit->setHtml(QCoreApplication::translate("set_help", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\350\207\252\345\212\250\350\256\276\347\275\256\357\274\232\347\202\271\345\207\273\345\220\216\357\274\214\346\214\211\347\205\247\345\275\223\345\211\215\351\242\204\350\256\276\347\232\204\346\244\215\347\211\251\347\232\204\347\211\271\346\200\247\357\274\214\350\207\252\345\212\250\350\256\276\347\275\256\345\275\223\345\211\215\345\217\202\346\225\260\347\232\204\344\270\212\351\231\220"
                        "\343\200\201\344\270\213\351\231\220\345\200\274\343\200\202\345\220\257\347\224\250\350\207\252\345\212\250\350\256\276\347\275\256\345\220\216\357\274\214\346\211\213\345\212\250\350\256\276\347\275\256\347\232\204\345\217\202\346\225\260\344\274\232\345\244\261\346\225\210\343\200\202</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\346\211\213\345\212\250\350\256\276\347\275\256\357\274\232\346\214\211\344\270\213\346\211\213\345\212\250\350\256\276\347\275\256\347\232\204\346\214\211\351\224\256\345\220\216\357\274\214\344\274\232\345\260\206\345\275\223\345\211\215\350\276\223\345\205\245\347\232\204\345\200\274\357\274\214\344\275\234\344\270\272\345\275\223\345\211\215\351\200\211\346\213\251\347\232\204\345\217\202\346\225\260\347\232\204\344\270\212\351\231\220\343\200\201\344\270\213\351\231\220\345\200\274\343\200\202</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class set_help: public Ui_set_help {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SET_HELP_H
