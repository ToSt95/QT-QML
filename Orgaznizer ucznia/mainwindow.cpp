#include "mainwindow.h"
#include "dialog.h"
#include "chart.h"
#include "ui_mainwindow.h"
#include "loginwindow.h"
#include <QTimer>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent,QString x) :
    QMainWindow(parent),
    idLog(x),
    ui(new Ui::MainWindow)
{
     ui->setupUi(this); //wskaźnik na elementy user interface


    //ODŚWIEŻANIE ZEGARA
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(show_time()));
    timer->start(1000);
    show_time();

    //WIADOMOŚCI
    model = new QStringListModel(this);
    model3 = new QStringListModel(this);

    ui->listView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //pola do prywatnych wiadomości
    ui->label_22->hide();
    ui->lineEdit_3->hide();
    ui->lineEdit_2->setPlaceholderText("Name...");
    ui->lineEdit_2->hide();
    ui->lineEdit_3->setPlaceholderText("Surname...");


    //wczytywanie obrazów
    QPixmap image(":/img/img/tt.png");
    ui->label_25->setPixmap(image);
    QPixmap image2(":/img/img/2.png");
    ui->label_26->setPixmap(image2);

    //WCZYTYWANIE DANYCH
    QSqlQuery qwr;
    if(qwr.exec("SELECT Imie,Nazwisko,e_mail,nr_tel,Klasy_idKlasa,obecnosci,nieobecnosci,klasy.Nazwa FROM uczniowie JOIN klasy ON uczniowie.Klasy_idKlasa = klasy.idKlasa WHERE idUczniowie='"+idLog+"'"))
    {
        if(qwr.next())
        {
            ui->label_4->setText(ui->label_4->text()+" "+qwr.value(0).toString());
            ui->label_6->setText(ui->label_6->text()+" "+qwr.value(1).toString());
            ui->label_8->setText(ui->label_8->text()+" "+qwr.value(2).toString());
            ui->label_10->setText(ui->label_10->text()+" "+qwr.value(3).toString());
            user_class = qwr.value(4).toString();
            imie_m = qwr.value(0).toString();
            nazwisko_m = qwr.value(1).toString();
            imie_nazwisko = qwr.value(0).toString() +" "+qwr.value(1).toString();
            ui->label_12->setText(ui->label_12->text()+" "+qwr.value(7).toString());
            ui->label_5->setText("<h1>"+qwr.value(7).toString()+"</h1>");
        }
        else
        {
            ui->label_24->setText("Information loading error");
        }
    }

    //USTAWIENIE OBRAZU SUDENTA

    if(imie_m[imie_m.size()-1] == "a")
    {
        QPixmap std(":/img/img/smile_T.png");
        ui->label_3->setPixmap(std);
    }
    else
    {
        QPixmap std(":/img/img/23.png");
        ui->label_3->setPixmap(std);
    }

    ui->pushButton_8->hide();


    //WCZYTANIE WIADOMOSCI I PRYWATNYCH WIADOMOSCI
    p_update_messages();
    update_messages();

    //USTAWIANIE LABEL Z IMIENIEM I NAZWISKIEM
    ui->label_13->setText(qwr.value(0).toString()+" "+qwr.value(1).toString());

    //LISTA UCZNIOW
    students = new QSqlQueryModel(this);
    students->setQuery("SELECT Imie,Nazwisko FROM uczniowie WHERE Klasy_idKlasa='"+qwr.value(4).toString()+"' ORDER BY Nazwisko ASC");
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
    else
    {
        ui->label_24->setText("Information loading error. Please restart application.");
    }

    grades_update();

   //WYSWIETLANIE PRAC DOMOWYCH
   QSqlQuery qwr_home;
   model2 = new QStringListModel(this);

   if(qwr_home.exec("SELECT *,przedmioty.Nazwa FROM pracaDomowa INNER JOIN przedmioty ON pracaDomowa.przedmioty_idPrzedmioty = przedmioty.idPrzedmioty WHERE uczniowie_idUczniowie='"+idLog+"'"))
   {
          while(qwr_home.next())
          {
            tittle_homework.append("Subject: "+qwr_home.value(7).toString()+" | Deadline: "+qwr_home.value(3).toString());
            homework.append(qwr_home.value(1).toString());
            id_homework.append(qwr_home.value(0).toString());
            rozw_home.append(qwr_home.value(2).toString());
          }

          model2->setStringList(tittle_homework);
          ui->listView_2->setModel(model2);
   }
   else
   {
       ui->label_24->setText("Information loading error. Please restart application.");
   }

   //PLAN
   plan = new QSqlQueryModel(this);
   plan->setQuery("SELECT Time,Monday,Tuesday,Wednesday,Thursday,Firday FROM plan");
   plan->setHeaderData(2,Qt::Vertical,8);
   ui->tableView_2->setModel(plan);
   ui->tableView_2->verticalHeader()->hide();
   ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}
MainWindow::~MainWindow()
{
    delete ui;
    delete model;
    delete model2;
    delete model3;
    delete timer2;
    delete timer3;
    delete plan;
    delete students;

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

    if(!ui->checkBox->isChecked())
    {
        tittle_messages.clear();
        messages.clear();
        QSqlQuery qwr_post;
        QString tittle = "["+QDateTime::currentDateTime().toString("dd/MM/yy hh:mm:ss")+"] by "+imie_nazwisko+" | "+ui->lineEdit->text();
        QString messag = ui->plainTextEdit->toPlainText();
        qwr_post.prepare("INSERT INTO wiadomosci (idWiadomosci, Tytul, Tresc, Data, uczniowie_idUczniowie, uczniowie_Klasy_idKlasa) VALUES (NULL, :tittle, :message, NULL, :id, :class)");
        qwr_post.bindValue(":id", idLog);
        qwr_post.bindValue(":tittle", tittle);
        qwr_post.bindValue(":class",  user_class);
        qwr_post.bindValue(":message", messag);
        qwr_post.exec();
        ui->label_24->setText("Post send.");
    }
    else
    {
        QString imie = ui->lineEdit_2->text();
        QString nazwisko = ui->lineEdit_3->text();
        bool check = false;
        QSqlQuery usr_test;
        if(usr_test.exec("SELECT idUczniowie FROM uczniowie WHERE Imie='"+imie+"' AND Nazwisko='"+nazwisko+"'"))
        {
            if(usr_test.next())
            {
                check = true;
            }
        }

        if(check)
        {
            {
                p_tittle_messages.clear();
                p_messages.clear();
                QSqlQuery qwr_privatte_message;
                QString p_tittle = "["+QDateTime::currentDateTime().toString("dd/MM/yy hh:mm:ss")+"] from "+imie_nazwisko+" | "+ui->lineEdit->text();
                QString p_messag = ui->plainTextEdit->toPlainText();
                qwr_privatte_message.prepare("INSERT INTO prywatneWiadomosci (idprywatneWiadomosci, Tytul, Tresc, uczniowie_idUczniowie, uczniowie_Klasy_idKlasa, Data, oImie, oNazwisko) VALUES (NULL, :tittle, :message, :id, :class, NULL,:oim,:onaz)");
                qwr_privatte_message.bindValue(":id", idLog);
                qwr_privatte_message.bindValue(":tittle", p_tittle);
                qwr_privatte_message.bindValue(":message", p_messag);
                qwr_privatte_message.bindValue(":oim", imie);
                qwr_privatte_message.bindValue(":class",  user_class);
                qwr_privatte_message.bindValue(":onaz", nazwisko);
                if(qwr_privatte_message.exec())
                ui->label_24->setText("Message send.");
            }
        }
        else
        {
           ui->label_24->setText("Wrong name or surname");
        }
    }
    update_messages();
    p_update_messages();

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
/*//WYBIERANIE ZDJECIA
void MainWindow::on_pushButton_8_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Open file"),"C://","All files (*.*)");
    QPixmap image(filename);
    int w = ui->label_3->width();
    int h = ui->label_3->height();
    ui->label_3->setPixmap(image.scaled(w,h));
    QSqlQuery inst;
    inst.exec("INSERT INTO uczniowie (img) VALUES ("+filename+") WHERE idUczniowie='"+idLog+"'" );
}*/
//UPDATE WIADOMOSCI
void MainWindow::update_messages()
{

    tittle_messages.clear();
    messages.clear();


    QSqlQuery usr3;
    if(usr3.exec("SELECT Tytul,Tresc FROM wiadomosci WHERE uczniowie_Klasy_idKlasa='"+user_class+"'"))
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
//update prywanych
void MainWindow::p_update_messages()
{

    p_tittle_messages.clear();
    p_messages.clear();


    QSqlQuery usr3;
    if(usr3.exec("SELECT Tytul,Tresc FROM prywatneWiadomosci WHERE oImie='"+imie_m+"' and oNazwisko='"+nazwisko_m+"'"))
    {
        while(usr3.next())
        {
            p_tittle_messages.append(usr3.value(0).toString());
            p_messages.append(usr3.value(1).toString());
        }
    }

    model3->setStringList(p_tittle_messages);
    ui->listView_3->setModel(model3);

}
//WYSWIETLANIE OCEN
void MainWindow::on_comboBox_currentIndexChanged()
{
    grades_update();
}
//REFRESH
void MainWindow::on_pushButton_12_clicked()
{
    tittle_messages.clear();
    messages.clear();
    update_messages();
}
//USUWANIE WIADOMOŚCI
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
            tittle_messages.clear();
            messages.clear();
            ui->textBrowser->clear();
            update_messages();
        }
        else
        {
            ui->label_24->setText("Information loading error. Please restart application.");
        }
    }

}
//BLOKADA SPAMOWANIA WIADOMOSCI
void MainWindow::odblokuj_dodawanie()
{
    timer2->stop();
    timer3 ->stop();
    ui->pushButton_5->setEnabled(true);
    ui->pushButton_5->setText("Add");
    licznik_timer =10;
}
//BLOKADA SPAMOWANIA WIADOMOSCI
void MainWindow::odliczanie()
{
    timer3->start();
    ui->pushButton_5->setText(QString::number(licznik_timer));
    licznik_timer--;
}
//WYSWIETLANIE PRACY DOMOWEJ Z WYBRANEGO PRZEDMIOTU
void MainWindow::on_listView_2_clicked(const QModelIndex &index)
{
    ui->textBrowser_2->setText(homework.at(index.row()));
    ui->textEdit->setText(rozw_home.at(index.row()));
}
//UPDATE PRACY DOMOWEJ
void MainWindow::on_pushButton_9_clicked()
{
    int i = ui->listView_2->currentIndex().row();
    QString c_id = id_homework.at(i);
    QString tr = ui->textEdit->toPlainText();
    QSqlQuery homee;
    homee.prepare("UPDATE pracaDomowa SET Rozwiazanie='"+tr+"' WHERE uczniowie_idUczniowie='5' AND idpracaDomowa='"+c_id+"'");
    homee.exec();
    rozw_home.replace(i,tr);
    ui->textEdit->setText(rozw_home.at(i));
}
//ON/OFF WIDOK PRYWATNEJ WIADOMOŚCI
void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->label_22->show();
        ui->lineEdit_3->show();
        ui->lineEdit_2->show();
    }
    else
    {
        ui->label_22->hide();
        ui->lineEdit_2->hide();
        ui->lineEdit_3->hide();
    }
}
//WYSWIETLANIE PRYWATNEJ WIADOMOSCI
void MainWindow::on_listView_3_clicked(const QModelIndex &index)
{
    ui->textBrowser_3->setText(p_messages.at(index.row()));
}
//USUWANIE PRYWATNEJ WIADOMOSCI
void MainWindow::on_pushButton_13_clicked()
{
    QSqlQuery qwr_grad;
    if(ui->listView_3->currentIndex().isValid())
    {
        QString mtd = p_tittle_messages.at(ui->listView_3->currentIndex().row());


        if(qwr_grad.exec("SELECT idprywatneWiadomosci,uczniowie_idUczniowie FROM prywatneWiadomosci WHERE Tytul='"+mtd+"'"))
        {
            if(qwr_grad.next())
            {
                QSqlQuery del;
                del.exec("DELETE FROM prywatneWiadomosci WHERE Tytul='"+mtd+"'");
            }

            p_tittle_messages.clear();
            p_messages.clear();
            ui->textBrowser_3->clear();
            p_update_messages();
        }
        else
        {
           ui->label_24->setText("Information loading error. Please restart application.");
        }

    }
}
//UPDATE PRYWATNE WIADOMOŚCI
void MainWindow::on_pushButton_14_clicked()
{
    p_update_messages();
}
//UPDATE OCEN
void MainWindow::grades_update()
{
    QSqlQuery qwr_grad;
    QString subject_name = ui->comboBox->currentText();
    QString current_subject_id;
    if(qwr_grad.exec("SELECT idPrzedmioty from przedmioty WHERE Nazwa='"+subject_name+"'"))
    {
       if(qwr_grad.next())
       {
        current_subject_id = qwr_grad.value(0).toString();
       }
       else
       {
           ui->label_24->setText("Information loading error. Please restart application.");
       }
    }
    QString grades_string="";
    double avr = 0;
    double count = 0;
    if(qwr_grad.exec("SELECT ocena from oceny WHERE Uczniowie_idUczniowie='"+idLog+"' AND Przedmioty_idPrzedmioty='"+current_subject_id+"'"))
    {
          while(qwr_grad.next())
          {
              grades_string +="|"+ qwr_grad.value(0).toString() + "|  ";
              avr += qwr_grad.value(0).toInt();
              count++;
          }

          avr = avr/count;
          ui->label_20->setText(grades_string);
          ui->label_20->setText("Subject: " +subject_name+"\n\n\n"+ui->label_20->text()+"\n\nAverage: "+QString::number(avr));
    }
    else
    {
        ui->label_24->setText("Information loading error. Please restart application.");
    }

}

//WCZYTYWANIE DANYCH STUDENTA
void MainWindow::loading_user_data(QString id)
{
    QSqlQuery qwr;
    if(qwr.exec("SELECT Imie,Nazwisko,e_mail,nr_tel,Klasy_idKlasa,klasy.Nazwa FROM uczniowie JOIN klasy ON uczniowie.Klasy_idKlasa = klasy.idKlasa WHERE idUczniowie='"+id+"'"))
    {
        if(qwr.next())
        {
            ui->label_4->setText("Name: "+qwr.value(0).toString());
            ui->label_6->setText("Surname: "+qwr.value(1).toString());
            ui->label_8->setText("E-mail: "+qwr.value(2).toString());
            ui->label_10->setText("Phone: "+qwr.value(3).toString());
        }
        else
        {
            ui->label_24->setText("Information loading error");
        }
     }
    ui->stackedWidget->setCurrentIndex(1);

}

//WYSWIETLANIE DANYCH STUDENTA PO KLIKNIECIU NA LISCIE
void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    int r = index.row();
    QString id;
    QModelIndex i_name = ui->tableView->model()->index(r,0);
    QModelIndex i_surname = ui->tableView->model()->index(r,1);
    QString name = ui->tableView->model()->data(i_name).toString();
    QString surname = ui->tableView->model()->data(i_surname).toString();


    QSqlQuery qwr;
    if(qwr.exec("SELECT idUczniowie FROM uczniowie  WHERE Imie='"+name+"' AND Nazwisko='"+surname+"'"))
    {
        if(qwr.next())
        {
            id = qwr.value(0).toString();
        }
        else
        {
            ui->label_24->setText("Information loading error");
        }
     }
    if(id != idLog && ui->label_4->text() != "Name: "+name )
    {
        if(name[name.size()-1] == "a")
        {
            QPixmap std(":/img/img/smile_T.png");
            ui->label_3->setPixmap(std);
        }
        else
        {
            QPixmap std(":/img/img/23.png");
            ui->label_3->setPixmap(std);
        }

        loading_user_data(id);
        ui->pushButton_8->show();
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(1);

    }


}
//POWROT DO SWOJEGO PROFILU
void MainWindow::on_pushButton_8_clicked()
{
    loading_user_data(idLog);
    if(imie_m[imie_m.size()-1] == "a")
    {
        QPixmap std(":/img/img/smile_T.png");
        ui->label_3->setPixmap(std);
    }
    else
    {
        QPixmap std(":/img/img/23.png");
        ui->label_3->setPixmap(std);
    }

     ui->pushButton_8->hide();
}
