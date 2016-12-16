/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *txtUser;
    QLineEdit *txtPassword;
    QLabel *lbl_status;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *btn_login;
    QPushButton *btn_clear;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(613, 350);
        label = new QLabel(Dialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 150, 51, 16));
        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 180, 51, 16));
        txtUser = new QLineEdit(Dialog);
        txtUser->setObjectName(QStringLiteral("txtUser"));
        txtUser->setGeometry(QRect(100, 150, 113, 20));
        txtPassword = new QLineEdit(Dialog);
        txtPassword->setObjectName(QStringLiteral("txtPassword"));
        txtPassword->setGeometry(QRect(100, 180, 113, 20));
        txtPassword->setEchoMode(QLineEdit::Password);
        lbl_status = new QLabel(Dialog);
        lbl_status->setObjectName(QStringLiteral("lbl_status"));
        lbl_status->setGeometry(QRect(80, 230, 211, 31));
        lbl_status->setFrameShape(QFrame::Box);
        lbl_status->setFrameShadow(QFrame::Raised);
        widget = new QWidget(Dialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(220, 150, 77, 54));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        btn_login = new QPushButton(widget);
        btn_login->setObjectName(QStringLiteral("btn_login"));

        verticalLayout->addWidget(btn_login);

        btn_clear = new QPushButton(widget);
        btn_clear->setObjectName(QStringLiteral("btn_clear"));

        verticalLayout->addWidget(btn_clear);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        label->setText(QApplication::translate("Dialog", "UserName", 0));
        label_2->setText(QApplication::translate("Dialog", "Password", 0));
        lbl_status->setText(QApplication::translate("Dialog", "Status: ", 0));
        btn_login->setText(QApplication::translate("Dialog", "Login", 0));
        btn_clear->setText(QApplication::translate("Dialog", "Clear", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
