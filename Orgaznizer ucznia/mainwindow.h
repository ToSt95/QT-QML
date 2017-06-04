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
    QString idLog;
    QString imie_nazwisko;
    QSqlQueryModel *students;
    int licznik_timer = 10;
    explicit MainWindow(QWidget *parent = 0,QString x ="5");
    void update_messages();
    ~MainWindow();

private slots:


    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_6_clicked();
    void on_listView_clicked(const QModelIndex &index);
    void on_pushButton_8_clicked();
    void on_pushButton_10_clicked();
    void on_comboBox_currentIndexChanged();
    void on_pushButton_12_clicked();
    void show_time();
    void on_pushButton_11_clicked();
    void odblokuj_dodawanie();
    void odliczanie();


    void on_listView_2_clicked(const QModelIndex &index);

    void on_pushButton_9_clicked();

private:
    Ui::MainWindow *ui;
    QStringListModel *model;
    QStringListModel *model2;
    QStringList tittle_messages;
    QStringList messages;
    QStringList tittle_homework;
    QStringList homework;
    QTimer *timer2;
    QTimer *timer3;


};

#endif // MAINWINDOW_H
