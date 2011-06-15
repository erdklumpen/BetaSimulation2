#-------------------------------------------------
#
# Project created by QtCreator 2011-06-08T18:23:49
#
#-------------------------------------------------

QT       += core gui \
            svg

TARGET = BetaSimulation2
TEMPLATE = app

CONFIG += qwt

LIBS += -lqwt

SOURCES += main.cpp\
        mainwindow.cpp \
    abstractca.cpp \
    castate.cpp \
    cahistory.cpp \
    settings.cpp \
    eca.cpp \
    runcawidget.cpp \
    testcawidget.cpp \
    gameoflife.cpp \
    minority.cpp

HEADERS  += mainwindow.h \
    abstractca.h \
    castate.h \
    cahistory.h \
    settings.h \
    eca.h \
    runcawidget.h \
    testcawidget.h \
    gameoflife.h \
    minority.h

FORMS    += mainwindow.ui \
    settings.ui \
    runcawidget.ui \
    testcawidget.ui
