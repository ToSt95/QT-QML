#-------------------------------------------------
#
# Project created by QtCreator 2017-05-29T22:05:30
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = stack
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    loginwindow.cpp \
    chart.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    loginwindow.h \
    chart.h

FORMS    += mainwindow.ui \
    dialog.ui \
    loginwindow.ui

RESOURCES += \
    res.qrc

win32: LIBS += -LD:/Programy/C_MSQL/lib/ -llibmysql

INCLUDEPATH += D:/Programy/C_MSQL/include
DEPENDPATH += D:/Programy/C_MSQL/include

DISTFILES += \
    img/img/2png.png \
    img/img/23.png
