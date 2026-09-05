/********************************************************************************
** Form generated from reading UI file 'ph_page.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PH_PAGE_H
#define UI_PH_PAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PH_page
{
public:
    QComboBox *comboBox;
    QLabel *label;
    QLineEdit *highPH;
    QLineEdit *lowPH;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *help_3;
    QPushButton *help_2;
    QPushButton *help_5;
    QPushButton *help_4;

    void setupUi(QWidget *PH_page)
    {
        if (PH_page->objectName().isEmpty())
            PH_page->setObjectName("PH_page");
        PH_page->resize(300, 200);
        PH_page->setMinimumSize(QSize(300, 200));
        PH_page->setMaximumSize(QSize(300, 200));
        comboBox = new QComboBox(PH_page);
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(130, 10, 89, 27));
        label = new QLabel(PH_page);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 10, 91, 19));
        highPH = new QLineEdit(PH_page);
        highPH->setObjectName("highPH");
        highPH->setGeometry(QRect(100, 50, 61, 27));
        lowPH = new QLineEdit(PH_page);
        lowPH->setObjectName("lowPH");
        lowPH->setGeometry(QRect(100, 90, 61, 27));
        label_2 = new QLabel(PH_page);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 50, 69, 19));
        label_3 = new QLabel(PH_page);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 90, 69, 19));
        pushButton = new QPushButton(PH_page);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(260, 160, 21, 21));
        pushButton_2 = new QPushButton(PH_page);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(50, 130, 61, 61));
        pushButton_3 = new QPushButton(PH_page);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(140, 130, 61, 61));
        help_3 = new QPushButton(PH_page);
        help_3->setObjectName("help_3");
        help_3->setGeometry(QRect(231, 40, 41, 41));
        help_2 = new QPushButton(PH_page);
        help_2->setObjectName("help_2");
        help_2->setGeometry(QRect(192, 40, 41, 41));
        help_5 = new QPushButton(PH_page);
        help_5->setObjectName("help_5");
        help_5->setGeometry(QRect(191, 80, 41, 41));
        help_4 = new QPushButton(PH_page);
        help_4->setObjectName("help_4");
        help_4->setGeometry(QRect(230, 80, 41, 41));

        retranslateUi(PH_page);

        QMetaObject::connectSlotsByName(PH_page);
    } // setupUi

    void retranslateUi(QWidget *PH_page)
    {
        PH_page->setWindowTitle(QCoreApplication::translate("PH_page", "Form", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("PH_page", "\350\215\211\350\216\223", nullptr));

        label->setText(QCoreApplication::translate("PH_page", "\350\207\252\345\212\250\350\256\276\347\275\256\351\200\211\351\241\271", nullptr));
        highPH->setText(QCoreApplication::translate("PH_page", "7.10", nullptr));
        lowPH->setText(QCoreApplication::translate("PH_page", "6.25", nullptr));
        label_2->setText(QCoreApplication::translate("PH_page", "\344\270\212\351\231\220PH", nullptr));
        label_3->setText(QCoreApplication::translate("PH_page", "\344\270\213\351\231\220PH", nullptr));
        pushButton->setText(QCoreApplication::translate("PH_page", "?", nullptr));
        pushButton_2->setText(QCoreApplication::translate("PH_page", "\346\211\213\345\212\250\350\256\276\347\275\256", nullptr));
        pushButton_3->setText(QCoreApplication::translate("PH_page", "\350\207\252\345\212\250\350\256\276\347\275\256", nullptr));
        help_3->setText(QCoreApplication::translate("PH_page", "-", nullptr));
        help_2->setText(QCoreApplication::translate("PH_page", "+", nullptr));
        help_5->setText(QCoreApplication::translate("PH_page", "+", nullptr));
        help_4->setText(QCoreApplication::translate("PH_page", "-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PH_page: public Ui_PH_page {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PH_PAGE_H
