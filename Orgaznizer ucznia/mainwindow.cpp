#include "mainwindow.h"
#include "dialog.h"
#include "chart.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QMessageBox>
#include <QFileDialog>
#include "loginwindow.h"
#include <QDebug>





MainWindow::MainWindow(QWidget *parent,QString x) :
    QMainWindow(parent),
    idLog(x),
    ui(new Ui::MainWindow)
{

     ui->setupUi(this);

    //ODŚWIEŻANIE ZEGARA

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(show_time()));
    timer->start(1000);
    show_time();


    //WIADOMOŚCI
    model = new QStringListModel(this);
    update_messages();


    //WCZYTYWANIE DANYCH
    QSqlQuery qwr;
    if(qwr.exec("SELECT Imie,Nazwisko,e_mail,nr_tel,Klasy_idKlasa,obecnosci,nieobecnosci FROM uczniowie WHERE idUczniowie='"+idLog+"'"))
    {
        if(qwr.next())
        {
            ui->label_5->setText(qwr.value(0).toString());
            ui->label_7->setText(qwr.value(1).toString());
            ui->label_9->setText(qwr.value(2).toString());
            ui->label_11->setText(qwr.value(3).toString());
        }
        else
        {
            ui->label_5->setText("Nie udało się pobrać danych");
        }
    }
    QSqlQuery qwr_class;
    QString id_class = qwr.value(4).toString();
    if(qwr_class.exec("SELECT Nazwa FROM klasy WHERE idKlasa='"+id_class+"'"))
    {
    if(qwr_class.next())
    {
        ui->label_17->setText(qwr_class.value(0).toString());
    }
    }

    //USTAWIANIE LABEL Z IMIENIEM I NAZWISKIEM
    ui->label_13->setText(qwr.value(0).toString()+" "+qwr.value(1).toString());

    //LISTA UCZNIOW
    students = new QSqlQueryModel(this);
    students->setQuery("SELECT Imie,Nazwisko FROM uczniowie WHERE Klasy_idKlasa='"+qwr.value(4).toString()+"' ");
    ui->tableView->setModel(students);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //OBECNOSC
    ui->label_14->setText("Presence: "+qwr.value(5).toString());
    ui->label_16->setText("Absence: "+qwr.value(6).toString());
    double perc = qwr.value(5).toInt()*100/(qwr.value(5).toInt() + qwr.value(6).toInt());
    ui->label_18->setText("% Presence: "+QString::number(perc) + "%");

    //WYKRES
    chart wykres(this,qwr.value(6).toInt(),qwr.value(5).toInt());
    ui->verticalLayout_6->addWidget(wykres.chartView);

    //WYŚWIETLANIE OCEN
      QSqlQuery qwr_grad;
      if(qwr_grad.exec("SELECT idPrzedmioty,Nazwa from przedmioty"))
      {
          while(qwr_grad.next())
          {
              QString res = qwr_grad.value(1).toString();
              ui->comboBox->addItem(res);
          }
      }

      QString nazw = ui->comboBox->currentText();
      QString ind;
      if(qwr_grad.exec("SELECT idPrzedmioty from przedmioty WHERE Nazwa='"+nazw+"'"))
      {
          if(qwr_grad.next())
          {
              ind = qwr_grad.value(0).toString();

          }
      }
      QString wynik="";
      double avr = 0;
      double liczba_ocen = 0;
      if(qwr_grad.exec("SELECT ocena from oceny WHERE Uczniowie_idUczniowie='"+idLog+"' AND Przedmioty_idPrzedmioty='"+ind+"'"))
      {
          while(qwr_grad.next())
          {
              wynik +="|"+ qwr_grad.value(0).toString() + "|  ";
              avr += qwr_grad.value(0).toInt();
              liczba_ocen++;
          }
      }
      avr = avr/liczba_ocen;
      ui->label_20->setText(wynik);
      ui->label_15->setText("Average: "+QString::number(avr));

      //WYSWIETLANIE PRAC DOMOWYCH
      QSqlQuery qwr_home;
      QSqlQuery qwr_sub;
      model2 = new QStringListModel(this);
      if(qwr_home.exec("SELECT * FROM pracaDomowa WHERE uczniowie_idUczniowie='"+idLog+"'"))
      {

          while(qwr_home.next())
          {
            qwr_sub.exec("SELECT Nazwa FROM przedmioty WHERE idPrzedmioty='"+qwr_home.value(5).toString()+"'");
            if(qwr_sub.next())
            {
            tittle_homework.append("Subject: "+qwr_sub.value(0).toString()+" | Deadline: "+qwr_home.value(3).toString());
            homework.append(qwr_home.value(1).toString());

            }
          }
      }
      model2->setStringList(tittle_homework);
      ui->listView_2->setModel(model2);




}



MainWindow::~MainWindow()
{
    delete ui;


}

//POTWIERDZENIE WYJŚCIA Z APP
void MainWindow::on_pushButton_4_clicked()
{
    QMessageBox::StandardButton replay;
    replay = QMessageBox::question(this,"Alert","Would you like to exit application?",QMessageBox::Yes | QMessageBox::No);
    if(replay==QMessageBox::Yes) this->close();
}

//NAWIGACJA PO ZAKŁADKACH stackedWidget
void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}
void MainWindow::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}
void MainWindow::on_pushButton_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);

}

//CZYSZCZENIE EKRANU WIADOMOSCI
void MainWindow::on_pushButton_6_clicked()
{
    ui->plainTextEdit->clear();
}

//WYŚWIETLANIE CZASU
void MainWindow::show_time()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm:ss");
    if ((time.second() % 2) == 0)
    {
          text[2] = ' ';
          text[5] = ' ';
    }

    ui->label->setText(text+"\n"+QDateTime::currentDateTime().toString("dddd dd MMMM yyyy"));
}

//DODAWANIE POSTA
void MainWindow::on_pushButton_5_clicked()
{
    timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(odblokuj_dodawanie()));


    tittle_messages.clear();
    messages.clear();

    QSqlQuery usr;
    if(usr.exec("SELECT Imie,Nazwisko FROM uczniowie WHERE idUczniowie='"+idLog+"'"))
    {
        if(usr.next())
        {
           imie_nazwisko = usr.value(0).toString()+" "+usr.value(1).toString();
        }
    }

    QSqlQuery usr2;
    QString tytul = "["+QDateTime::currentDateTime().toString("dd/MM/yy hh:mm:ss")+"] by "+imie_nazwisko+" | "+ui->lineEdit->text();
    QString wiadomosc = ui->plainTextEdit->toPlainText();
    usr2.prepare("INSERT INTO wiadomosci (idWiadomosci, Tytul, Tresc, Data, uczniowie_idUczniowie, uczniowie_Klasy_idKlasa) VALUES (NULL, :tittle, :message, NULL, :id, 3)");
    usr2.bindValue(":id", idLog);
    usr2.bindValue(":tittle", tytul);
    usr2.bindValue(":message", wiadomosc);
    usr2.exec();

    update_messages();

    timer3 = new QTimer(this);
    connect(timer3, SIGNAL(timeout()), this, SLOT(odliczanie()));
    timer3->start(1000);
    ui->pushButton_5->setText(QString::number(licznik_timer));
    licznik_timer--;
    ui->pushButton_5->setEnabled(false);
    timer2->start(10000);

    ui->plainTextEdit->clear();
    ui->lineEdit->clear();
}

//WYSWIETLANIE ZAZNACZONEJ WIADOMOSCI
void MainWindow::on_listView_clicked(const QModelIndex &index)
{

    ui->textBrowser->setText(messages.at(index.row()));
}

//WYBIERANIE ZDJECIA
void MainWindow::on_pushButton_8_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Open file"),"C://","All files (*.*)");
    QPixmap image(filename);
    int w = ui->label_3->width();
    int h = ui->label_3->height();
    ui->label_3->setPixmap(image.scaled(w,h));
}

//UPDATE WIADOMOSCI
void MainWindow::update_messages()
{
    QString imie_nazwisko;
    QSqlQuery usr;
    if(usr.exec("SELECT Imie,Nazwisko FROM uczniowie WHERE idUczniowie='"+idLog+"'"))
    {
        if(usr.next())
        {
           imie_nazwisko = usr.value(0).toString()+" "+usr.value(1).toString();
        }
    }

    QSqlQuery usr3;
    if(usr3.exec("SELECT Tytul,Tresc FROM wiadomosci"))
    {
        while(usr3.next())
        {

           tittle_messages.append(usr3.value(0).toString());
           messages.append(usr3.value(1).toString());

        }
    }

    model->setStringList(tittle_messages);
    ui->listView->setModel(model);
}

//WYSWIETLANIE OCEN
void MainWindow::on_comboBox_currentIndexChanged()
{
    double avr = 0;
    double liczba_ocen = 0;
    QString nazw = ui->comboBox->currentText();
    QString ind;
    QSqlQuery qwr_grad;
    if(qwr_grad.exec("SELECT idPrzedmioty from przedmioty WHERE Nazwa='"+nazw+"'"))
    {
        if(qwr_grad.next())
        {
            ind = qwr_grad.value(0).toString();
        }
    }
    QString wynik="";
    if(qwr_grad.exec("SELECT ocena from oceny WHERE Uczniowie_idUczniowie='"+idLog+"' AND Przedmioty_idPrzedmioty='"+ind+"'"))
    {
        while(qwr_grad.next())
        {
            wynik +="|"+ qwr_grad.value(0).toString() + "|  ";

            avr += qwr_grad.value(0).toInt();
            liczba_ocen++;
        }
    }
    avr = avr/liczba_ocen;
    ui->label_20->setText(wynik);
    ui->label_15->setText("Average: "+QString::number(avr));
}
//REFRESH
void MainWindow::on_pushButton_12_clicked()
{
    tittle_messages.clear();
    messages.clear();

    update_messages();
}

//POPRAWIĆ DA SIĘ ZROBIĆ DUŻO LEPIEJ
void MainWindow::on_pushButton_11_clicked()
{
    QSqlQuery qwr_grad;
    if(ui->listView->currentIndex().isValid())
    {
    QString mtd = tittle_messages.at(ui->listView->currentIndex().row());


    if(qwr_grad.exec("SELECT idWiadomosci,uczniowie_idUczniowie FROM wiadomosci WHERE Tytul='"+mtd+"'"))
    {
        if(qwr_grad.next() && qwr_grad.value(1).toString() == idLog)
        {
            QSqlQuery del;
            del.exec("DELETE FROM wiadomosci WHERE Tytul='"+mtd+"'");
        }
    }

    tittle_messages.clear();
    messages.clear();
    ui->textBrowser->clear();
    update_messages();
    }

}
void MainWindow::odblokuj_dodawanie()
{
    timer2->stop();
    timer3 ->stop();
    ui->pushButton_5->setEnabled(true);
    ui->pushButton_5->setText("Add");
    licznik_timer =10;

}
void MainWindow::odliczanie()
{

    timer3->start();
    ui->pushButton_5->setText(QString::number(licznik_timer));
    licznik_timer--;

}

void MainWindow::on_listView_2_clicked(const QModelIndex &index)
{
    ui->textBrowser_2->setText(homework.at(index.row()));
}

void MainWindow::on_pushButton_9_clicked()
{

}
