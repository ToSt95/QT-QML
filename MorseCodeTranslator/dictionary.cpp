#include "dictionary.h"

Dictionary::Dictionary(QObject *parent) : QObject(parent)
{
    // big letters
    alphabetOfMorse.insert('a',".-");
    alphabetOfMorse.insert('b',"-...");
    alphabetOfMorse.insert('c',"-.-.");
    alphabetOfMorse.insert('d',"-..");
    alphabetOfMorse.insert('e',".");
    alphabetOfMorse.insert('f',"..-.");
    alphabetOfMorse.insert('g',"--.");
    alphabetOfMorse.insert('h',"....");
    alphabetOfMorse.insert('i',"..");
    alphabetOfMorse.insert('j',".---");
    alphabetOfMorse.insert('k',"-.-");
    alphabetOfMorse.insert('l',".-..");
    alphabetOfMorse.insert('m',"--");
    alphabetOfMorse.insert('n',"-.");
    alphabetOfMorse.insert('o',"---");
    alphabetOfMorse.insert('p',".--.");
    alphabetOfMorse.insert('q',"--.-");
    alphabetOfMorse.insert('r',".-.");
    alphabetOfMorse.insert('s',"...");
    alphabetOfMorse.insert('t',"-");
    alphabetOfMorse.insert('u',"..-");
    alphabetOfMorse.insert('v',"...-");
    alphabetOfMorse.insert('w',".--");
    alphabetOfMorse.insert('x',"-..-");
    alphabetOfMorse.insert('y',"-.--");
    alphabetOfMorse.insert('z',"--..");

    // digits
    alphabetOfMorse.insert('0',"-----"); // 0
    alphabetOfMorse.insert('1',".----");
    alphabetOfMorse.insert('2',"..---");
    alphabetOfMorse.insert('3',"...--");
    alphabetOfMorse.insert('4',"....-");
    alphabetOfMorse.insert('5',".....");
    alphabetOfMorse.insert('6',"-....");
    alphabetOfMorse.insert('7',"--...");
    alphabetOfMorse.insert('8',"---..");
    alphabetOfMorse.insert('9',"----."); // 9

    // other characters
    alphabetOfMorse.insert(';',"-.-.-."); // ;
    alphabetOfMorse.insert(':',"---..."); // :
    alphabetOfMorse.insert(',',".----."); // '
    alphabetOfMorse.insert('"',".-..-."); // "
    alphabetOfMorse.insert('/',"-..-."); // /
    alphabetOfMorse.insert('\\',".-..."); // \ //
    alphabetOfMorse.insert('=',"-...-"); // =
    alphabetOfMorse.insert('+',".-.-."); // +
    alphabetOfMorse.insert('-',"-....-"); // -
    alphabetOfMorse.insert('_',"..--.-"); // _
    alphabetOfMorse.insert(')',"-.--.-"); // )
    alphabetOfMorse.insert('(',"-.--."); // (
    alphabetOfMorse.insert('^',".-.-."); // ^
    alphabetOfMorse.insert('%',"...-."); // %
    alphabetOfMorse.insert('$',".-..."); // $
    alphabetOfMorse.insert('@',"...-.-"); // @
    alphabetOfMorse.insert('~',"-.-.-"); // ~
    alphabetOfMorse.insert('.',".-.-.-"); // .
    alphabetOfMorse.insert(',',"--..--"); // ,
    alphabetOfMorse.insert('?',"..--.."); // ?
    alphabetOfMorse.insert('!',"-.-.--"); // ?

}

QString Dictionary::getMorseCharacter(QChar normalCharacter)
{
    return alphabetOfMorse.value(normalCharacter);
}

QChar Dictionary::getNormalCharacter(QString morseCharacter)
{
    return alphabetOfMorse.key(morseCharacter);
}
