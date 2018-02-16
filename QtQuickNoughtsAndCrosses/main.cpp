#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "gamemanager.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    GameManager gameManager;

    return app.exec();
}
