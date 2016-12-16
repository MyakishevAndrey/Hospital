#include "manager.h"
#include "ui_manager.h"
#include "QStandardItemModel"
#include "QStandardItem"
#include "QTableView"
#include <QSqlQueryModel>

Manager::Manager( QSqlDatabase db,QStackedWidget *pointStack_, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Manager)
{
    myDBm=db;
    pointStack=pointStack_;

       ui->setupUi(this);
}

Manager::~Manager()
{
    delete ui;
}


void Manager::on_pushButton_find_clicked()
{
    if(!myDBm.isOpen())
    {
        qDebug()<<"No connection to DB!"<<endl;
        return;
    }
    QString name_doctor, surname_doctor, middle_name_doctor;
    name_doctor=ui->line_name->text();
    surname_doctor=ui->line_surname->text();
    middle_name_doctor=ui->line_middle_name->text();

    QSqlQuery qry_doc, qry_email, qry_phone;
    QString name_department,email, phone, number;
    if(qry_doc.exec("SELECT Name_otdel from Department join Doctor where "
                    "Doctor.id_otdel=Department.id_otdel and Doctor.Name=\'"+name_doctor+"\' "
                    "and Doctor.Last_Name=\'"+surname_doctor+"\' and Doctor.Middle_Name=\'"+middle_name_doctor+"\';"))
    {
        if(qry_doc.next())
        {
            name_department=qry_doc.value(0).toString();//запоминаем название отделения, где работает доктор
        }
        else
        {
            name_doctor="Вы ввели несуществующего доктора!";
        }

    }
   if(qry_email.exec("SELECT email from Emails_Doctors join Doctor on "
                     "Emails_Doctors.id_doctor=Doctor.id_doctor where Last_Name=\'"+surname_doctor+"\' and Name=\'"+name_doctor+"\' and Middle_Name=\'"+middle_name_doctor+"\' ;"))
    {
      if(qry_email.next())
      {
         email=qry_email.value(0).toString();
      }
    }
   if(qry_phone.exec("SELECT phone from Phones_Doctors join Doctor on  Phones_Doctors.id_doctor=Doctor.id_doctor where"
                     " Last_Name=\'"+surname_doctor+"\' and Name=\'"+name_doctor+"\' and Middle_Name=\'"+middle_name_doctor+"\';"))
   {
       if(qry_phone.next())
       {
          phone=qry_phone.value(0).toString();
       }

   }
   if(name_doctor!="Вы ввели несуществующего доктора!")
   {
    QString data_doctors="Отделение: "+name_department+"\nТелефон: "+phone+"\nE-mail: "+email+"\n";
    ui->text_edit_inf_o_doctore->setText(data_doctors);
   }
   else
   {
       ui->text_edit_inf_o_doctore->setText("Вы ввели несуществующего доктора!");
   }
}

void Manager::on_line_middle_name_textChanged(const QString &arg1)
{
    ui->pushButton_find->setEnabled(true);
}

void Manager::on_pushButton_clicked()
{
    qApp->exit();
}

void Manager::on_pushButton_back_clicked()
{
    pointStack->setCurrentIndex(0);//указатель на стек указывает на первую форму (форму dialog)

    ui->line_name->clear();
    ui->line_middle_name->clear();
    ui->line_surname->clear();
    ui->text_edit_inf_o_doctore->clear();

}
