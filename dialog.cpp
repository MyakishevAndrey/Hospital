#include "dialog.h"
#include "ui_dialog.h"
#include <QtWidgets>
#define Path_to_db "D:/Hospital/Hospital.sqlite"

Dialog::Dialog(QSqlDatabase db, QStackedWidget* pointStack_, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    myDBm=db;
    pointStack=pointStack_;
    ui->setupUi(this);

    QFileInfo checkFile(Path_to_db); //обьект класса, предоставляющего информацию о свойствах файла
    if(checkFile.isFile())//проверка, на существование файла
    {
        if(myDBm.open())//если существует файл Hospital.sqlite, то открываем его
        {
            ui->lbl_status->setText(" Connected to Database file: ");//если он открылся то выводим сообщение в label_status
        }
    }
    else//если файла не существует
    {
      ui->lbl_status->setText(" Database file does not exist: ");//то в label выводится сообщение что не удалось подключиться к БД
    }
}

Dialog::~Dialog()
{
    delete ui;
    qDebug()<<"Closing the connection...";
}


void Dialog::on_btn_login_clicked()
{
    QString Username, Password;
    Username=ui->txtUser->text();//вытаскиваем через метод text() текст, введенный в txtUser и сохраняем его в переменную Username
    Password=ui->txtPassword->text();

    if(!myDBm.isOpen())
    {
     qDebug()<<"No connection to DB!";
     return;
    }
    QSqlQuery qry;//обьект класса QSqlQuery, запрос
    if(qry.exec("SELECT name_user, password, role, id_worker, id_zap from users where name_user=\'"+Username+
                "\' and password=\'"+Password+"\'"))//отправляет запрос в БД, где Username - это имя, введенное через форму,Password-пароль, введенный через форму
    {
        if(qry.next())//если запись найдена, перемещаем указатель к первой записи результата запроса
        {
            ui->lbl_status->setText("Valid Username, Password");//в lbl_status вывод поясняющего сообщения о том, что все хорошо

            QString message="Добро пожаловать в БД.\nВаша роль: "+qry.value(2).toString()+"\n";
            QMessageBox::warning(this, "Login was successful", message);//выводится сообщение о удачном подкючении к БД
            id=qry.value(4).toInt();//запоминаем id_zap из запроса
            if(id==0)
            {
                QComboBox* combo = new QComboBox(this);
                //Добавить элементы выпадающего списка
               combo->addItem("Авторизация"); //имеет индекс 0 в стеке, т.к добавляется в стек первым
               combo->addItem("Работник регистратуры");
               combo->addItem("Доктор");
               combo->addItem("Менеджер");

               combo->show();


               QObject::connect(combo, SIGNAL(activated(int)), pointStack, SLOT(setCurrentIndex(int)));
            }
            else
            {
                pointStack->setCurrentIndex(id);
            }

        }
        else//если запись не найдена
        {
            ui->lbl_status->setText("Wrong Username or Password");
        }
    }
}


void Dialog::on_pushButton_Exit_clicked()
{
    qApp->exit();
}
