#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMainWindow>
namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

    void setOk(bool x);
    QString getIdLogowania();


private slots:
    void on_pushButton_clicked();
    void logowanie();




private:
    Ui::LoginWindow *ui;
    QSqlQueryModel *qu;
    bool ok = false;
    QString idLogowania;

};

#endif // LOGINWINDOW_H
