#include "mainwindow.h"
#include <QApplication>
//main
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Dziennik wychowawcy");
    w.show();

    return a.exec();
}
