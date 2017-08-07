#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtTest/QTest>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    set = new Download();





}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->textBrowser->setText("Please wait...");
    QString lang;

    if(ui->radioButton->isChecked())
    {
       lang = "pl-en";
    }
    else
    {
       lang = "en-pl";
    }
    QString word = ui->lineEdit->text();
    set->makeRequest("https://translate.yandex.net/api/v1.5/tr/translate?key=//keyAPIhere//"+word+"&lang="+lang+"&[format=html]");
    QTest::qWait(1000);
    ui->textBrowser->setText(set->get_result());

}
