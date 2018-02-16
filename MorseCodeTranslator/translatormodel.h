#ifndef TRANSLATORMODEL_H
#define TRANSLATORMODEL_H

#include <QObject>
#include <QDebug>
#include "dictionary.h"

class TranslatorModel : public QObject
{
    Q_OBJECT
public:
    explicit TranslatorModel(QObject *parent = 0);
    void setNormalText(QString text);
    void setMorseCodeText(QString text);
    const QString &getMorseCodeText();
    const QString &getNormalText();

signals:
    void translateToMorseTextComplete(); //signal that is emit when translation from normal text to Morse code is complete
    void translateToNormalTextComplete();//signal that is emit when translation from Morse code text to normal text is complete
    void errorAppears(QString sourceName,QString message); //signal emit when error occurs

public slots:
    void tranlateToMorseCode(); //translate to morse text slot handler
    void tranlateToNormalText(); //translate to normal text slot handler

private:
    QString normalText;
    QString morseCodeText;
    Dictionary *morseDictionary; //dictionary with each character of morse and latin alphaber
};

#endif // TRANSLATORMODEL_H
