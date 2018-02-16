#include "translatormodel.h"

TranslatorModel::TranslatorModel(QObject *parent) : QObject(parent)
{
    //sets starts values to each text
    normalText = "";
    morseCodeText = "";
    morseDictionary = new Dictionary(this);
}

void TranslatorModel::tranlateToMorseCode()
{
    morseCodeText = "";

    if(normalText != nullptr) // if edit text is not empty
    {
        QStringList wordsToTranslate;
        wordsToTranslate = normalText.split(" "); // spliting text form text edit by " "
        QString normalWord = "";
        int currentWordPosition = 0;

        foreach(normalWord,wordsToTranslate)
        {
            ++currentWordPosition;

            for(int currentPosition = 0; currentPosition < normalWord.length(); ++currentPosition)
            {

                QChar singleCharacter = normalWord.at(currentPosition).toLower(); //changing character to lower

                morseCodeText += morseDictionary->getMorseCharacter(singleCharacter);

                if(currentPosition <= normalWord.length()) morseCodeText += " "; // get extra space at end of character
            }

            if(currentWordPosition != wordsToTranslate.length()) morseCodeText += " "; //get extra space at end of word
        }

        emit translateToMorseTextComplete();
    }
    else
    {
        emit errorAppears("normalText","Normal text edit is empty!");
    }

}

void TranslatorModel::tranlateToNormalText()
{
    normalText ="";

    if(morseCodeText != nullptr)
    {
        QStringList wordsToTranslate;
        wordsToTranslate = morseCodeText.split(" ");
        QString morseWord = "";
        int currentWordPosition = 0;

        foreach(morseWord,wordsToTranslate)
        {
            ++currentWordPosition;

            if(morseWord != "")
            {
                normalText += morseDictionary->getNormalCharacter(morseWord);
            }
            else if (normalText[normalText.size()-1] != " ")
            {
                normalText += " ";
            }
        }

        emit translateToNormalTextComplete();
    }
    else
    {
        emit errorAppears("morseText","Morse code text edit is empty!");
    }
}

void TranslatorModel::setNormalText(QString text)
{
    normalText = text;
}

void TranslatorModel::setMorseCodeText(QString text)
{
    morseCodeText = text;
}

const QString &TranslatorModel::getMorseCodeText()
{
    return morseCodeText;
}

const QString &TranslatorModel::getNormalText()
{
    return normalText;
}
