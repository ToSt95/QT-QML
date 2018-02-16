#include "gamemanager.h"

GameManager::GameManager(QObject *parent) : QObject(parent)
{
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    setStartValues();
    connectAllFields();
    clearboardInfo();
    QObject::connect(restartButton,SIGNAL(restartGameButtonClicked()),this,SLOT(restartButtonCliced()));
}

void GameManager::boardFieldClicked()
{
    currentField = qobject_cast<QQuickItem*> (QObject::sender()); // get access to specific field pointer

    if(currentPlayer == playerOneNickname) // case player one turn
    {
        currentField->setProperty("imgUrl","qrc:/IMG/circle.png");// set QML propery in order to change field img
        int row = QQmlProperty::read(currentField, "rowInfo").toInt()-1; //set position of clicked field in board
        int column = QQmlProperty::read(currentField, "columnInfo").toInt()-1;
        boardFieldsPosition[row][column] = 1;
        currentField->disconnect(currentField,SIGNAL(fieldClicked()),this,SLOT(boardFieldClicked())); //discconnect slot in order to disable a field
    }
    else // case player two turn
    {
        currentField->setProperty("imgUrl","qrc:/IMG/cross.png"); // set QML propery in order to change field img
        currentField->disconnect(currentField,SIGNAL(fieldClicked()),this,SLOT(boardFieldClicked()));//discconnect slot in order to disable a field
        int row = QQmlProperty::read(currentField, "rowInfo").toInt() - 1; //set position of clicked field in board
        int column = QQmlProperty::read(currentField, "columnInfo").toInt()- 1;
        boardFieldsPosition[row][column] = 2;
    }

    if(checkWin()) //checking win condition
    {

    }
    else //if win condition not meet, change players
    {
        changeCurrentPlayer();
    }
}

void GameManager::restartButtonCliced()
{
    clearboardInfo();
    connectAllFields();
    changeCurrentPlayer();

    for (int positionInArray=0; positionInArray<9; ++positionInArray)
    {
        arrayOfBoardFields[positionInArray]->setProperty("imgUrl","qrc:/IMG/blank.jpg");
        arrayOfBoardFields[positionInArray]->setProperty("color","white");
    }
}

void GameManager::clearboardInfo()
{
    for(int i =0; i<3; i++)
    {
        for(int j = 0; j<3; j++)
        {
            boardFieldsPosition[i][j] = 0;
        }
    }

    turnCounter = 0;
}

void GameManager::disconnectAllFields()
{
    for (int positionInArray=0; positionInArray<9; ++positionInArray)
    {
        QObject::disconnect(arrayOfBoardFields[positionInArray],SIGNAL(fieldClicked()),this,SLOT(boardFieldClicked()));
    }
}

void GameManager::connectAllFields()
{
    for (int positionInArray=0; positionInArray<9; ++positionInArray)
    {
        QObject::connect(arrayOfBoardFields[positionInArray],SIGNAL(fieldClicked()),this,SLOT(boardFieldClicked()));
    }
}

void GameManager::setRedLine(int position1, int position2, int position3)
{
    arrayOfBoardFields[position1] ->setProperty("color","red");
    arrayOfBoardFields[position2] ->setProperty("color","red");
    arrayOfBoardFields[position3] ->setProperty("color","red");
}

void GameManager::setWonBoard()
{
    playersLabel->setProperty("text",currentPlayer+" WON!!!");

    if(currentPlayer == playerOneNickname)
    {
        playerOneScore++;
    }
    else if(currentPlayer == playerTwoNickname)
    {
        playerTwoScore++;
    }
    overallScore = "( O ) "+QString::number(playerOneScore)+":"+QString::number(playerTwoScore)+" ( X )";
    scoreLabel->setProperty("text",overallScore);
    disconnectAllFields();
}

void GameManager::changeCurrentPlayer()
{
    if(currentPlayer == playerOneNickname)
    {
        currentPlayer = playerTwoNickname;
    }
    else
    {
        currentPlayer = playerOneNickname;
    }

    playersLabel->setProperty("text","Turn: " + currentPlayer);
}

void GameManager::setStartValues()
{
    playerOneNickname = "PLAYER1";
    playerTwoNickname = "PLAYER2";
    currentPlayer = playerOneNickname;
    playerOneScore = 0;
    playerTwoScore = 0;
    overallScore = "( O ) "+QString::number(playerOneScore)+":"+QString::number(playerTwoScore)+" ( X )";

    QWindow* window = qobject_cast<QWindow*> (engine.rootObjects().at(0)); // pointer to ApplicationWindow in QML
    QQuickItem *fields = qobject_cast<QQuickItem*>(window->children().at(0)); // pointer to Rectangle with id fields
    QObject* grid = fields->children().at(1); // pointer to GridLayout with id grid

    playersLabel = (window->children().at(1))->children().at(1); //pointer to Text component in QML with id currentPlayer label
    restartButton = window->children().at(1); //pointer to Button component in QML with id restartButton
    scoreLabel = (window->children().at(1))->children().at(2);//pointer to Text component in QML with id scoreLabel
    scoreLabel->setProperty("text",overallScore);

    for (int positionInArray=0; positionInArray<9; ++positionInArray) // set values of arrayOfBoardFields by pointers to each field
    {
        boardField = grid->children().at(positionInArray);
        arrayOfBoardFields[positionInArray] = boardField;
    }
}

bool GameManager::checkWin()
{
    turnCounter++; // increment turns

    //check all possible conditions in order to win game
    if(boardFieldsPosition[0][0] == boardFieldsPosition[0][1] && boardFieldsPosition[0][1] == boardFieldsPosition[0][2] && boardFieldsPosition[0][0] != 0)
    {
        setRedLine(0,1,2); //set winning combination at board to red
        setWonBoard();//set winning player label, score
        return true;
    }
    else if(boardFieldsPosition[1][0] == boardFieldsPosition[1][1] && boardFieldsPosition[1][1] == boardFieldsPosition[1][2] && boardFieldsPosition[1][0] != 0)
    {
        setRedLine(3,4,5);
        setWonBoard();
        return true;
    }
    else if(boardFieldsPosition[2][0] == boardFieldsPosition[2][1] && boardFieldsPosition[2][1] == boardFieldsPosition[2][2] && boardFieldsPosition[2][0] != 0)
    {
        setRedLine(6,7,8);
        setWonBoard();
        return true;

    }
    else if(boardFieldsPosition[0][0] == boardFieldsPosition[1][0] && boardFieldsPosition[1][0] == boardFieldsPosition[2][0] && boardFieldsPosition[0][0] != 0)
    {
          setRedLine(0,3,6);
          setWonBoard();
          return true;
    }
    else if(boardFieldsPosition[0][1] == boardFieldsPosition[1][1] && boardFieldsPosition[1][1] == boardFieldsPosition[2][1] && boardFieldsPosition[0][1] != 0 )
    {
         setRedLine(1,4,7);
         setWonBoard();
         return true;
    }
    else if(boardFieldsPosition[0][2] == boardFieldsPosition[1][2] && boardFieldsPosition[1][2] == boardFieldsPosition[2][2] && boardFieldsPosition[0][2] != 0)
    {
        setRedLine(2,5,8);
        setWonBoard();
        return true;

    }
    else if(boardFieldsPosition[0][0] == boardFieldsPosition[1][1] && boardFieldsPosition[1][1] == boardFieldsPosition[2][2] && boardFieldsPosition[0][0] != 0)
    {
        setRedLine(0,4,8);
        setWonBoard();
        return true;

    }
    else if(boardFieldsPosition[0][2] == boardFieldsPosition[1][1] && boardFieldsPosition[1][1] == boardFieldsPosition[2][0] && boardFieldsPosition[0][2] != 0)
    {
        setRedLine(2,4,6);
        setWonBoard();
        return true;
    }

    else if(turnCounter == 9)
    {
        //draw case
        playersLabel->setProperty("text","DRAW...");
        return true;

    }
    else
    {
        return false;
    }
}
