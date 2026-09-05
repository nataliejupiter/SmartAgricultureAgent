/********************************************************************************
** Form generated from reading UI file 'welcome.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELCOME_H
#define UI_WELCOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_welcome
{
public:
    QLabel *title;

    void setupUi(QWidget *welcome)
    {
        if (welcome->objectName().isEmpty())
            welcome->setObjectName("welcome");
        welcome->resize(944, 693);
        title = new QLabel(welcome);
        title->setObjectName("title");
        title->setGeometry(QRect(30, 70, 571, 181));
        title->setStyleSheet(QString::fromUtf8("font: 600 32pt \"Segoe UI Variable Small Semibol\";"));

        retranslateUi(welcome);

        QMetaObject::connectSlotsByName(welcome);
    } // setupUi

    void retranslateUi(QWidget *welcome)
    {
        welcome->setWindowTitle(QCoreApplication::translate("welcome", "Form", nullptr));
        title->setText(QCoreApplication::translate("welcome", "\346\254\242 \350\277\216 \344\275\277 \347\224\250 \346\231\272 \346\205\247 \345\206\234 \344\270\232 \347\263\273 \347\273\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class welcome: public Ui_welcome {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOME_H
