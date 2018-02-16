#ifndef MAINTRANSLATORWINDOW_H
#define MAINTRANSLATORWINDOW_H

#include <QMainWindow>
#include "translatorgui.h"

namespace Ui {
class MainTranslatorWindow;
}

class MainTranslatorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainTranslatorWindow(QWidget *parent = 0);
    ~MainTranslatorWindow();

private:
    Ui::MainTranslatorWindow *ui;
    translatorGUI *view;
};

#endif // MAINTRANSLATORWINDOW_H
