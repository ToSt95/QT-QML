#include "loginwindow.h"
#include "mainwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    if(ok == true)
    {
        ui->label_3->setText("<font color='red'>[Błąd] Błąd połączenia z bazą danych</font>");

    }
    else
    {
        ui->label_3->setText("<font color='green'>[Połączono]</font>");

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
                win->setFixedSize(QSize(940, 580));
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

void LoginWindow::setOk(bool x)
{
    this->ok = x;
}

QString LoginWindow::getIdLogowania()
{
    return idLogowania;
}

