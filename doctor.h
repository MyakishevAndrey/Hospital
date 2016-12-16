#ifndef DOCTOR_H
#define DOCTOR_H
#include "dialog.h"
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
#include <QSqlQueryModel>
#include <QStringListModel>

namespace Ui
{
class doctor;
}

class doctor : public QWidget
{
    Q_OBJECT

public:
    explicit doctor( QSqlDatabase db,QStackedWidget *pointStack_,  QWidget *parent = 0 );
    ~doctor();
     QStackedWidget *pointStack;

private slots:
    void on_pushButton_2_clicked();

    void on_txtReccomendation_textChanged();

    void on_pushButton_Insert_clicked();

    void on_pushButton_clicked();

    void on_pushButton_back_clicked();

    void on_pushButton_clear_clicked();

private:
    Ui::doctor *ui;
    QSqlDatabase myDBm;
    QString id_doc, Name_Doctor, Last_Name_Doctor, Middle_Name_Doctor;
    QString mainDiagnosis, date_meeting, recomendations, time_meeting;
    QString Name_Client, Last_Name_Client, Middle_Name_Client, id_Client, Data_Birth;
};

#endif // DOCTOR_H
