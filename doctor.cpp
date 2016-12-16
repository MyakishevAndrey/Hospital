#include "doctor.h"
#include <time.h>
#include "ui_doctor.h"
#include <QTime>
#include "dialog.h"
doctor::doctor(QSqlDatabase db,QStackedWidget *pointStack_, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::doctor)
{
    myDBm=db;
    pointStack=pointStack_;
    ui->setupUi(this);
}

doctor::~doctor()
{
    delete ui;
}

void doctor::on_pushButton_2_clicked()//нажатие на кнопку Найти, форма doctor.ui
{
    //вытаскиваем ФИО клиента из формы doctor.ui
    Name_Client=ui->ln_Name->text();
    Last_Name_Client=ui->ln_Last_Name->text();
    Middle_Name_Client=ui->line_middle_name->text();

    if(!myDBm.isOpen())
    {
     qDebug()<<"No connection to DB!";
     return;
    }

    QSqlQuery qry;//обьект класса QSqlQuery, запрос
    //отправляем запрос на выполнение
    if(qry.exec("SELECT c.id_client, c.Name, c.Last_Name, c.Middle_Name FROM Client c where Name=\'"+Name_Client+"\' and Last_Name=\'"+Last_Name_Client+"\';"))
    {

        if(qry.next())//если запрос что-то вернул
        {
            if((qry.value(1).toString()==Name_Client)&(qry.value(2).toString()==Last_Name_Client)&(qry.value(3).toString()==Middle_Name_Client))
            {
                QString dataPaz="Пациент:\nИмя: "+Name_Client+"\nФамилия: "+Last_Name_Client+"\nОтчество: "+Middle_Name_Client+"\n";
                ui->textEdit->setText(dataPaz);
                id_Client=qry.value(0).toString();
                qDebug()<<id_Client<<endl;
            }

        }
        else//если запрос ничего не вернул
        {
            ui->textEdit->setText("Вы ввели несуществующего пациента!");
        }

    }
    //Запрос для вытаскивания id_doctor, Date_priem по клиенту
    QSqlQuery qry_1;
    if(qry_1.exec("SELECT id_doctor, Date_priem from Shedule where Shedule.id_client=\'"+id_Client+"\';"))
    {
        while(qry_1.next())//id_doctor за всю историю болезни клиента может быть много, поэтому используем while
        {
            id_doc=qry_1.value(0).toString();
            date_meeting=qry_1.value(1).toString();
            QSqlQuery qry_2;
            if(qry_2.exec("SELECT Name, Last_Name, Middle_Name from Doctor where Doctor.id_doctor=\'"+id_doc+"\'"))
            {
                if(qry_2.next())
                {
                    Name_Doctor=qry_2.value(0).toString();
                    Last_Name_Doctor=qry_2.value(1).toString();
                    Middle_Name_Doctor=qry_2.value(2).toString();
                }
            }
        }

    }

    QString dataPaz="Пациент:\nИмя: "+Name_Client+"\nФамилия: "+Last_Name_Client+"\nОтчество: "+Middle_Name_Client+"\nЗаписан к доктору: "+Last_Name_Doctor+" "+Name_Doctor+" "+Middle_Name_Doctor+"\nНа время: "+date_meeting+"\n";
    ui->textEdit->setText(dataPaz);

}

//если ввели текст в txtReccomendation, то кнопка pushButton_Insert(заполнить)становится активной
void doctor::on_txtReccomendation_textChanged()
{
    ui->pushButton_Insert->setEnabled(true);
}

void doctor::on_pushButton_Insert_clicked()
{
    mainDiagnosis=ui->lineDiagn->text();//вытаскиваем текст, введенный в lineDiagn
    recomendations=ui->txtReccomendation->toPlainText();//вытаскиваем текст, введенный в txtReccomendation

    if(!myDBm.isOpen())
    {
     qDebug()<<"No connection to DB!";
     return;
    }

    QSqlQuery qry_3;//обьект класса QSqlQuery, запрос

    //метод exec отправляет запрос на выполнение
    if(qry_3.exec("INSERT INTO notes (id_line, mainDiagnos, dateMeeting, id_client, id_doctor, recomendations) VALUES (NULL,\'"+mainDiagnosis+"\',\'"+date_meeting+"\',\'"+id_Client+"\', \'"+id_doc+"\',\'"+recomendations+"\' );"))
    {
        //Label - отражающий состояние Insert
        //Запись успешно внесена в БД
        ui->lbl_Insert->setText("Запись успешно внесена в БД!");
    }

}

void doctor::on_pushButton_clicked()
{
    qApp->exit();
}

void doctor::on_pushButton_back_clicked()
{
    pointStack->setCurrentIndex(0);//указатель на стек указывает на первую форму (форму dialog)
    ui->ln_Last_Name->clear();
    ui->ln_Name->clear();
    ui->line_middle_name->clear();
    ui->lineDiagn->clear();
    ui->txtReccomendation->clear();
    ui->textEdit->clear();
    ui->lbl_Insert->clear();
}

void doctor::on_pushButton_clear_clicked()
{
    ui->ln_Last_Name->clear();
    ui->ln_Name->clear();
    ui->line_middle_name->clear();
    ui->lineDiagn->clear();
    ui->txtReccomendation->clear();
    ui->textEdit->clear();
    ui->lbl_Insert->clear();
}
