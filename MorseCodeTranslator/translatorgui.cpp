#include "translatorgui.h"
#include "ui_translatorgui.h"

translatorGUI::translatorGUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::translatorGUI)
{
    ui->setupUi(this);
    translatorModel = new TranslatorModel(this);

    // connecting all signal and slots

    connect(ui->normalTextEdit,&QPlainTextEdit::textChanged,this,&translatorGUI::normalTextChanged);

    connect(ui->morseCodeTextEdit,&QPlainTextEdit::textChanged,this,&translatorGUI::morseCOdeTextChanged);

    connect(ui->translateToMorseButton,&QPushButton::clicked,translatorModel,&TranslatorModel::tranlateToMorseCode);

    connect(ui->translateToNormalTextButton,&QPushButton::clicked,translatorModel,&TranslatorModel::tranlateToNormalText);

    connect(translatorModel,&TranslatorModel::translateToMorseTextComplete,this,&translatorGUI::UpdateMorseCodeText);

    connect(translatorModel,&TranslatorModel::translateToNormalTextComplete,this,&translatorGUI::UpdateNormalText);

    connect(ui->loadNormalTextButton,&QPushButton::clicked,this,&translatorGUI::openNormalTextFile);

    connect(ui->loadMorseCodeTextButton,&QPushButton::clicked,this,&translatorGUI::openMorseCodeTextFile);

    connect(ui->saveNormalTextButton,&QPushButton::clicked,this,&translatorGUI::saveNormalTextFile);

    connect(ui->saveMorseCodeTextButton,&QPushButton::clicked,this,&translatorGUI::saveMorseCodeTextFile);

    connect(translatorModel, SIGNAL(errorAppears(QString,QString)),this, SLOT(errorMessageHandle(QString,QString)) );
}

translatorGUI::~translatorGUI()
{
    delete ui;
}

QString translatorGUI::openFile()
{
    QString fileContent;
    fileContent = "";
    QString newFileName = QFileDialog::getOpenFileName(this);
    if (!newFileName.isEmpty())
    {
        QFile file (newFileName);
        if (file.open (QFile::ReadOnly | QFile::Text))
        {
            QTextStream in(&file);
            fileContent = in.readAll();
            file.close();
        }
    }
    return fileContent;
}

void translatorGUI::saveFile(QString fileContent)
{
    QString newFileName = QFileDialog::getSaveFileName(this);
    if(!newFileName.isEmpty())
    {
        QFile file (newFileName);
        if (file.open (QFile::WriteOnly | QFile::Text))
        {
            QTextStream out (&file);
            out << fileContent;
            file.close();
        }
    }
}

void translatorGUI::normalTextChanged()
{
    translatorModel->setNormalText(ui->normalTextEdit->toPlainText());
}

void translatorGUI::morseCOdeTextChanged()
{
    translatorModel->setMorseCodeText(ui->morseCodeTextEdit->toPlainText());
}

void translatorGUI::UpdateMorseCodeText()
{
    ui->morseCodeTextEdit->setPlainText(translatorModel->getMorseCodeText());
}

void translatorGUI::UpdateNormalText()
{
    ui->normalTextEdit->setPlainText(translatorModel->getNormalText());
}

void translatorGUI::openMorseCodeTextFile()
{
    QString text = openFile();
    translatorModel->setMorseCodeText(text);
    ui->morseCodeTextEdit->setPlainText(text);
}

void translatorGUI::openNormalTextFile()
{
    QString text = openFile();
    translatorModel->setNormalText(text);
    ui->normalTextEdit->setPlainText(text);
}

void translatorGUI::saveNormalTextFile()
{
    QString fileContent;
    fileContent =  ui->normalTextEdit->toPlainText();
    saveFile(fileContent);
}

void translatorGUI::saveMorseCodeTextFile()
{
    QString fileContent;
    fileContent =  ui->morseCodeTextEdit->toPlainText();
    saveFile(fileContent);
}

void translatorGUI::errorMessageHandle(QString sourceName,QString message)
{
    if(sourceName == "normalText")
        ui->normalTextEdit->setPlaceholderText(message);
    else
        ui->morseCodeTextEdit->setPlaceholderText(message);
}

