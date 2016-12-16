#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDebug> //работает как cout: qDebug()<<"Hello";
#include <QtSql/QSql>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QStackedWidget>
#include <QComboBox>
#include <QHBoxLayout>
#include <QSqlQueryModel>

namespace Ui //пространство имен для формы
{
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
private:
     Ui::Dialog* ui; //указатель на форму(dialog.ui)
     QSqlDatabase myDBm;//обьект базы данных
     QStackedWidget* pointStack;
     int id;// имя роли в базе данных
public:
    explicit Dialog( QSqlDatabase db, QStackedWidget* pointStack_, QWidget* parent = 0);//parent - указатель на родительский класс
    ~Dialog();

    int getIdRole()
    {
        return id;//возвращаем ID роли
    }

private slots:

    void on_btn_login_clicked();

    void on_pushButton_Exit_clicked();

public:
   friend int getIdWorker(Dialog &obj);
};

#endif // DIALOG_H
