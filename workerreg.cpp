#include "workerreg.h"
#include "ui_workerreg.h"

WorkerReg::WorkerReg( QSqlDatabase db,QStackedWidget *pointStack_, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkerReg)
{
    myDBm=db;
    pointStack=pointStack_;
    ui->setupUi(this);
}

WorkerReg::~WorkerReg()
{
    delete ui;
}

void WorkerReg::on_AddButton_clicked() //Найти/Добавить клиента
{  //Ищем в БД клиента или добавляем нового

    if(!myDBm.isOpen())
    {
     qDebug()<<"No connection to DB!";
     return;
    }

    surname_client=ui->lineEdit_Surname->text();
    name_client=ui->lineEdit_Name->text();
    middle_name_client=ui->lineEdit_Middle_Name->text();


    QSqlQuery qry;//обьект класса QSqlQuery, запрос

    //метод exec отправляет запрос на выполнение
    if(qry.exec("SELECT id_client FROM Client where Name=\'"+name_client+"\' and Last_Name=\'"+surname_client+"\' and Middle_Name=\'"+middle_name_client+"\';"))
    {
       //если не нашел имя или фамилию или имя - в if не зайдет
        if(qry.next())//если запись найдена, перемещаем указатель к первой записи результата запроса
        {
            ui->label_5->setText("Клиент найден в БД!");//Label - отражающий состояние
            id_client=qry.value(0).toString();//запоминаем id клиента
        }
        else//если id_client не нашел в БД
        {
            QSqlQuery qry_for_insert;//обьект класса QSqlQuery, запрос для внесения клиента

            if(qry_for_insert.exec("INSERT INTO Client(id_client, Name, Last_Name, Middle_Name, id_ZapKar) VALUES (NULL,\'"+name_client+"\',\'"+surname_client+"\',\'"+middle_name_client+"\',NULL);"))
            {
            //Label - отражающий состояние Insert
            //Запись успешно внесена в БД
           ui->label_5->setText("Клиент добавлен в БД!");

           QSqlQuery qry_id_client;//обьект запроса для получения id только что внесенного клиента

           if(qry_id_client.exec("Select id_client from client where name=\'"+name_client+"\' and last_name=\'"+surname_client+"\' and Middle_Name=\'"+middle_name_client+"\';"))
           {
               if(qry_id_client.next())
               {
                   id_client=qry_id_client.value(0).toString();
               }
           }
         }
        }

    QSqlQuery qry_department;//создаем обьект запроса для поиска отделений
    //Вытаскиваем все отделения из БД
    if(qry_department.exec("SELECT Name_otdel FROM Department;"))//к обьекту запроса применяется метод exec
    {
        QSqlQueryModel* model = new QSqlQueryModel();//создали обьект класса для представления Sql Запроса
        model->setQuery(qry_department);//в эту модель отправили результат Sql-запроса qry(весь столбце отделений отправляет в model
        ui->listView->setModel(model);//на listView помещается модель
    }
}
}

void WorkerReg::on_listView_clicked(const QModelIndex &index)//кликаем на выбранное отделение в ListView
{
    QString name, last_name, middle_name;
   //Qt::DisplayRole показывает информацию из выделенной строки
    name_department=index.data(Qt::DisplayRole).toString();//получаем название выбранного отделения
    //The key data to be rendered in the form of text -выбранные данные представляются в виде текста

    QSqlQuery qry;//обьект запроса в БД для вытаскивания докторов из отделения
    QString strDataDoctors;//строка для склеивания фамилии, имя, отчества доктора
    QStringList lstDataDoctors;//QStringListModel требует список как аргумент

    if(qry.exec("SELECT Name, Last_Name, Middle_Name from Doctor join Department on department.id_otdel=doctor.id_otdel where department.Name_otdel=\'"+name_department+"\';"))
    {

       while(qry.next())
       {
        name=qry.value(0).toString();
        last_name=qry.value(1).toString();
        middle_name=qry.value(2).toString();

        strDataDoctors=name+" "+middle_name+" "+last_name;
        lstDataDoctors<<strDataDoctors;//помещаем в список QStringList строку о докторе

       }
        QStringListModel* mod = new QStringListModel();
        mod->setStringList(lstDataDoctors);//устанавливается модель со списком докторов

        ui->listView_2->setModel(mod);//отображается модель
    }
}

void WorkerReg::on_listView_2_clicked(const QModelIndex &index)
{
    name_doctor=index.data(Qt::DisplayRole).toString();//получаем информацию о докторе
    QStringList name=name_doctor.split(QRegExp("\\s"));//разделяем строку доктора на 3 части по пробелу
    QStringListModel* mod = new QStringListModel();
    QSqlQuery qry;//обьект запроса в БД для вытаскивания даты приема и номера кабинета для выбранного доктора
    QStringList lst;
    QString strData;//список строк куда будем помещать дату и номер кабинета
    QString date_p, num_cab;

    if(qry.exec("SELECT Date_priem, Number_cabinet from Shedule join Doctor on Doctor.id_doctor=Shedule.id_doctor where Shedule.id_client is NULL and Last_Name=\'"+name[2]+"\'"))
    {
        if(!qry.next())
        {
           QString informationMes="Доктор занят!";
           lst<<informationMes;
           mod->setStringList(lst);//устанавливается модель со списком докторов
           ui->listView_time->setModel(mod);
        }
        else
        {
            date_p=qry.value(0).toString();
            num_cab=qry.value(1).toString();

            strData=date_p+"/ Номер кабинета: "+num_cab;
            lst<<strData;//помещаем в список строку дату и номер кабинета
            mod->setStringList(lst);//устанавливается модель со списком докторов
            ui->listView_time->setModel(mod);

         while(qry.next())
         {
            date_p=qry.value(0).toString();
            num_cab=qry.value(1).toString();

            strData=date_p+"/ Номер кабинета: "+num_cab;
            lst<<strData;//помещаем в список строку дату и номер кабинета
         }
            mod->setStringList(lst);//устанавливается модель со списком докторов
            ui->listView_time->setModel(mod);
        }
    }


    QSqlQuery qry_id_doc;//обьект запроса в БД для вытаскивания id_doctor по фамилии
    if(qry_id_doc.exec("SELECT id_doctor from Doctor where Last_Name=\'"+name[2]+"\';"))
    {
        if(qry_id_doc.next())
        {
            id_doctor=qry_id_doc.value(0).toString();
        }
    }
}
void WorkerReg::on_listView_time_clicked(const QModelIndex &index)
{
    data=index.data().toString();//после клика на listView с датами, запоминаем выбранную дату в поле класса
    qDebug()<<data<<endl;
    data_for_upd=data.split('/',QString::SkipEmptyParts);
    qDebug()<<data_for_upd<<endl;
    data_for_up=data_for_upd.at(0);
}
void WorkerReg::on_pushButton_talon_clicked()
{
    QSqlQuery qry_upd;//обьект для UPDATE столбца id_client таблицы Shedule
    if(qry_upd.exec("UPDATE Shedule set id_client="+id_client+" where id_doctor="+id_doctor+" and Date_priem=\'"+data_for_up+"\';"))
    {
       ui->label_update->setText("Запись добавлена в БД");

    }
    QString dataTalon="ТАЛОН:\nДата: "+data+"\nОтделение: "+name_department+"\nИмя доктора: "+name_doctor+"\n";
    ui->textEdit->setText(dataTalon);

}

void WorkerReg::on_push_Exit_clicked()
{
    qApp->exit();
}

void WorkerReg::on_pushButton_clear_clicked()
{
   ui->lineEdit_Name->clear();
   ui->lineEdit_Surname->clear();
   ui->lineEdit_Middle_Name->clear();
}

void WorkerReg::on_pushButton_back_clicked()
{
    pointStack->setCurrentIndex(0);//указатель на стек указывает на первую форму (форму dialog)
    ui->lineEdit_Name->clear();
    ui->lineEdit_Surname->clear();
    ui->lineEdit_Middle_Name->clear();
    ui->label_update->setText("Статус");
    ui->label_5->clear();
    ui->textEdit->clear();

    QStringList lst;
    QStringListModel* mod = new QStringListModel();
    mod->setStringList(lst);
    ui->listView->setModel(mod);
    ui->listView_2->setModel(mod);
    ui->listView_time->setModel(mod);

}
