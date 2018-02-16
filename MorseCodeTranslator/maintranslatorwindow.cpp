#include "maintranslatorwindow.h"
#include "ui_maintranslatorwindow.h"
#include "ui_translatorgui.h"

MainTranslatorWindow::MainTranslatorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainTranslatorWindow)
{
    ui->setupUi(this);
    view = new translatorGUI(this);
    this->setCentralWidget(view);

}

MainTranslatorWindow::~MainTranslatorWindow()
{
    delete ui;
}
