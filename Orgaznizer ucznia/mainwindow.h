#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QStringList>
#include <QMessageBox>
#include <QSqlQueryModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString idLog;                                              //USER ID
    QString imie_nazwisko;                                      //USER NAME SURNAME
    int licznik_timer = 10;                                     //TIMER COUNTER USED TO BLOCKING ADD BUTTON FOR 10s

    explicit MainWindow(QWidget *parent = 0,QString x ="5");

    void update_messages();                                     //UPDATE POSTS
    void p_update_messages();                                   //UPDATE PRIVATE MESSAGES
    void grades_update();                                       //UPDATE GRADES

    ~MainWindow();

private slots:


    void on_pushButton_4_clicked();                              //"Exit" BUTTON
    void on_pushButton_3_clicked();                              //"Send" BUTTON
    void on_pushButton_clicked();                                //"Messages" BUTTON
    void on_pushButton_2_clicked();                              //"Calendar" BUTTON
    void on_pushButton_5_clicked();                              //"Sent"->"Add" BUTTON
    void on_pushButton_7_clicked();                              //"Account" BUTTON
    void on_pushButton_6_clicked();                              //"Sent"->"Clear" BUTTON
    void on_pushButton_13_clicked();                             //"Messages"->private->"Delete" BUTTON
    void on_pushButton_14_clicked();                             //"Messages"->private->"Refresh" BUTTON
    void on_pushButton_8_clicked();                              //"Choose file" BUTTON
    void on_pushButton_10_clicked();                             //"Class" BUTTON
    void on_pushButton_9_clicked();                              //"Submit" homework BUTTON
    void on_pushButton_12_clicked();                             //"Messages"->post->"Delete" BUTTON
    void on_pushButton_11_clicked();                             //"Messages"->post->"Refresh" BUTTON

    void on_comboBox_currentIndexChanged();
    void on_checkBox_stateChanged(int arg1);
    void on_listView_2_clicked(const QModelIndex &index);
    void on_listView_clicked(const QModelIndex &index);
    void on_listView_3_clicked(const QModelIndex &index);
    void show_time();
    void odliczanie();
    void odblokuj_dodawanie();

private:
    Ui::MainWindow *ui;
    QStringListModel *model;
    QStringListModel *model2;
    QStringListModel *model3;
    QTimer *timer2;
    QTimer *timer3;
    QSqlQueryModel *students;
    QSqlQueryModel *plan;
    QStringList tittle_messages;
    QStringList messages;
    QStringList p_tittle_messages;
    QStringList p_messages;
    QStringList tittle_homework;
    QStringList homework;
    QStringList id_homework;
    QStringList rozw_home;
    QString user_class;



};

#endif // MAINWINDOW_H
