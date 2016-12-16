#ifndef MANAGER_H
#define MANAGER_H
#include <QWidget>
#include <QDebug>
#include <QtSql/QSql>
#include <QFileInfo>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QStringListModel>
#include <QtSql/QSqlQuery>
#include "dialog.h"

namespace Ui {

class Manager;
}

class Manager : public QWidget
{
    Q_OBJECT

public:
    explicit Manager( QSqlDatabase db, QStackedWidget* pointStack_,  QWidget* parent = 0);
    QString id_doc;
    QStackedWidget *pointStack;

    ~Manager();

private slots:

    void on_pushButton_find_clicked();

    void on_line_middle_name_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_back_clicked();

private:
    Ui::Manager *ui;
    QSqlDatabase myDBm;//обьект базы данных
};

#endif // MANAGER_H
