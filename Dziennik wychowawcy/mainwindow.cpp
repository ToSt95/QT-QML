#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    db  = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("tutor");
    db.setUserName("root");
    db.setPassword("");


    if(!db.open())
    {
        ui->label_3->setText("<font color='red'>[Błąd] Błąd połączenia z bazą danych</font>");
    }
    else
    {
        ui->label_3->setText("<font color='green'>[Połączono] Zaloguj by zobaczyć listę uczniów </font>");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();
}

void MainWindow::logowanie()
{
    if(ui->login->text().toStdString() != "" && ui->password->text().toStdString() != "" )
    {
        QString log = ui->login->text();
        QString pass = ui->password->text();


        QSqlQuery qwr;


        if(qwr.exec("SELECT * FROM teachers WHERE login='"+log+"' AND password='"+pass+"'"))
        {
            if(qwr.next())
            {
                qu = new QSqlQueryModel (this);
                qu->setQuery("SELECT name,surname,grade FROM students");
                ui->tableView->setModel(qu);

                ui->label_3->setText("<font color='green'>[Zalogowano] Witaj "+qwr.value(1).toString()+" "+qwr.value(2).toString()+"!<font>");
                ui->login->setDisabled(1);
                ui->password->setDisabled(1);
                ui->pushButton->setText("Wyjscie");
                islog=1;


            }

            else
            {
                ui->label_3->setText("<font color='red'>[Błąd] Błędne dane logowania</font>");

            }

        }




    }

}

void MainWindow::on_pushButton_clicked()
{
    if(islog != 1)
    logowanie();
    else
    {
       this->close();
    }
}
