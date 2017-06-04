#include "loginwindow.h"
#include "mainwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    db  = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("sql8.freesqldatabase.com");
    db.setDatabaseName("sql8177950");
    db.setUserName("sql8177950");
    db.setPassword("69IrLi5uwH");
    db.setPort(3306);

    if(!db.open())
    {
        ui->label_3->setText("<font color='red'>[Błąd] Błąd połączenia z bazą danych</font>");
    }
    else
    {
        ui->label_3->setText("<font color='green'>[Połączono] Zaloguj by zobaczyć listę uczniów </font>");
    }

}

LoginWindow::~LoginWindow()
{
    delete ui;

}

void LoginWindow::on_pushButton_clicked()
{
    logowanie();
}

void LoginWindow::logowanie()
{
    if(ui->lineEdit->text().toStdString() != "" && ui->lineEdit_2->text().toStdString() != "" )
    {
        QString log = ui->lineEdit->text();
        QString pass = ui->lineEdit_2->text();


        QSqlQuery qwr;


        if(qwr.exec("SELECT idUczniowie FROM uczniowie WHERE login='"+log+"' AND password='"+pass+"'"))
        {
            if(qwr.next())
            {
                idLogowania = qwr.value(0).toString();
                MainWindow *win  = new MainWindow(0,idLogowania);

                win->setFixedSize(QSize(840, 480));

                win->setWindowTitle("Organizer Alpha");

                this->close();
                win->show();

            }

            else
            {
                ui->label_3->setText("<font color='red'>[Błąd] Błędne dane logowania</font>");

            }

        }




    }

}
