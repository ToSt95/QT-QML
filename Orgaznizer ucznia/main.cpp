#include "mainwindow.h"
#include "loginwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow w;
    w.setFixedSize(QSize(450, 115));

    w.setWindowTitle("Login to Organizer Alpha");
    w.show();

    return a.exec();
}
