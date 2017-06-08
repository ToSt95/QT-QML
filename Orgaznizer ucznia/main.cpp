#include "mainwindow.h"
#include "loginwindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow w;
    w.setFixedSize(QSize(450, 115));
    w.setWindowTitle("Login to Organizer Alpha");
    QSqlDatabase db;
    db  = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("sql8.freesqldatabase.com");
    db.setDatabaseName("sql8177950");
    db.setUserName("sql8177950");
    db.setPassword("69IrLi5uwH");
    db.setPort(3306);
    if(!db.open())
    {
       w.setOk(false);
    }
    else
    {
       w.setOk(true);

    }

    w.show();


    int r = a.exec();

    if(db.open())
    {
        db.close();
        QSqlDatabase::removeDatabase("QMYSQL");
        qDebug() << "Closing";
    }


    return r;
}
