#include "dialog.h"
#include "doctor.h"
#include "workerreg.h"
#include "manager.h"
#include <QApplication>
#include <QTextCodec>
#define Path_to_db "D:/Hospital/Hospital.sqlite"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase myDB;//обьект базы данных
    myDB=QSqlDatabase::addDatabase("QSQLITE");//имя приложения, с которой работаем
    myDB.setDatabaseName(Path_to_db);//путь до базы данных

    QWidget* pMainWindow = new QWidget;//указатель на управляющее окно

    //получаем указатель на стек Widget - ов
    //явно по стеку может перемещаться только Admin
    QStackedWidget* stack = new QStackedWidget(); //new вернет указатель на область памяти, где разместится stack

    // виджет, добавленный в стек получает свой ID
    //в таком же порядке будет выпадающий список

    //Создаем четыре окна(формы)
    Dialog* loginForm = new Dialog(myDB,stack);
    doctor* doctorForm = new doctor(myDB,stack);
    WorkerReg* workerRegistForm = new WorkerReg(myDB,stack);
    Manager* managerForm = new Manager(myDB,stack);


    stack->addWidget(loginForm);//0
    stack->addWidget(workerRegistForm);//1
    stack->addWidget(doctorForm);//2
    stack->addWidget(managerForm);//3


    //установка шаблона окна, класс QHBoxLayout используется для размещения обьектов на окне в горизонтальной компоновке
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(stack);//добавляем на форму  в горизонтальной компоновке четыре формы (не будут активны единовременно)

    pMainWindow->setLayout(layout);//задаём горизонтальную компановку главного окна
    pMainWindow->resize(800, 500);//размеры главного окна по горизонтали/вертикали
    pMainWindow->show();

    pMainWindow->setWindowTitle("Больница");//задать заголовок главного окна




    return a.exec();
}
