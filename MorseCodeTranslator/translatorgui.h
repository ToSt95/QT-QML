#ifndef TRANSLATORGUI_H
#define TRANSLATORGUI_H

#include <QWidget>
#include "translatormodel.h"
#include <QFileDialog>
#include <QFile>

namespace Ui {
class translatorGUI;
}

class translatorGUI : public QWidget
{
    Q_OBJECT

public:
    explicit translatorGUI(QWidget *parent = 0);
    ~translatorGUI();


private:
    Ui::translatorGUI *ui;
    TranslatorModel *translatorModel; //pointer to translatorModel class with implementation of program logic
    QString openFile();
    void saveFile(QString fileContent);

public slots:
    void normalTextChanged(); //handle normal text update value in model
    void morseCOdeTextChanged();//handle morse cOde update value in model
    void UpdateMorseCodeText(); //handle morse code update in GUI
    void UpdateNormalText(); //handle normal text update in GUI
    void openMorseCodeTextFile();//handle open a file with morse code
    void openNormalTextFile();//handle open a file with NormalText
    void saveNormalTextFile();//handle save to file
    void saveMorseCodeTextFile();
    void errorMessageHandle(QString sourceName,QString message);//error messages handler

};

#endif // TRANSLATORGUI_H
