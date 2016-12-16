#ifndef WORKERREG_H
#define WORKERREG_H

#include <QWidget>
#include <QtSql/QSql>
#include <QFileInfo>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QStackedWidget>
#include <QComboBox>
#include <QHBoxLayout>
#include <QDebug>
#include <QStringListModel>
#include <QSqlQueryModel>
#include <QLayout>
#include <QFile>

namespace Ui {
class WorkerReg;
}

class WorkerReg : public QWidget
{
    Q_OBJECT

public:
    explicit WorkerReg( QSqlDatabase db, QStackedWidget* pointStack_,  QWidget* parent = 0 );
    QString name_client, surname_client, middle_name_client, name_doctor;
    QString data, num_cabinet, data_for_up;
    QString name_department;
    QString id_doctor, id_client;
    QStackedWidget* pointStack;
    QStringList data_for_upd;
    ~WorkerReg();

private slots:

    void on_AddButton_clicked();

    void on_listView_clicked(const QModelIndex &index);

    void on_listView_2_clicked(const QModelIndex &index);

    void on_pushButton_talon_clicked();

    void on_listView_time_clicked(const QModelIndex &index);

    void on_push_Exit_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_back_clicked();

private:
    Ui::WorkerReg *ui;
    QSqlDatabase myDBm;
signals:

};

#endif // WORKERREG_H
