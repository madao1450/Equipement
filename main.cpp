
#include "mainwindow.h"

#include <QApplication>
#include<QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    qDebug()<<QSqlDatabase::drivers();
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3305);
    db.setDatabaseName("equipmentManagement");
    db.setUserName("root");
    db.setPassword("123456");
    if (!db.open())
        qDebug()<<"can't open!"<<db.lastError();
    else
        qDebug()<<"open!";



    w.show();
    return a.exec();
}

