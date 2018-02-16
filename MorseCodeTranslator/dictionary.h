#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QObject>
#include <QMap>


class Dictionary : public QObject
{
    Q_OBJECT
public:
    explicit Dictionary(QObject *parent = 0);
    QString getMorseCharacter(QChar normalCharacter); // return string with morse character
    QChar getNormalCharacter(QString morseCharacter); // return QChar with normal character

signals:

public slots:

private:
    QMap<QChar,QString> alphabetOfMorse; // dictionary
};

#endif // DICTIONARY_H
