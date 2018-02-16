#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQuickItem>
#include <QQmlProperty>
#include <QDebug>


class GameManager : public QObject
{
    Q_OBJECT
public:
    explicit GameManager(QObject *parent = 0);

signals:


public slots:
    void boardFieldClicked();
    void restartButtonCliced();

private:
    QQmlApplicationEngine engine;

    QString currentPlayer;
    QString overallScore;
    int playerOneScore;
    int playerTwoScore;
    QString playerOneNickname;
    QString playerTwoNickname;

    int turnCounter;
    QObject *scoreLabel; //pointer to score label QML object
    QObject *playersLabel; //pointer to current player label QML object
    QObject *boardField;
    QObject *currentField; //pointer to field that emit signal fieldClicked
    QObject *restartButton;//pointer to restart button QML object

    QObject* arrayOfBoardFields[9]; // arrays of pointers to each board fields
    int boardFieldsPosition[3][3]; // information of status board used to check win condition

    void clearboardInfo(); // setting all cell  of boardFieldsPosition table to 0, 0 - empty field, 1 - player one marked field, 2 - player two marked field
    void disconnectAllFields();//disconnect all fields signal to slot handler
    void connectAllFields(); //connect all fields signal to slot handler
    void setRedLine(int,int,int); //function used to mark win condition on board
    void setWonBoard();
    void changeCurrentPlayer(); // change players
    void setStartValues(); // set starts valuse
    bool checkWin();
};

#endif // GAMEMANAGER_H
