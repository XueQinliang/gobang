#-------------------------------------------------
#
# Project created by QtCreator 2018-07-08T18:14:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gobang
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    boardwindow.cpp \
    solve.cpp \
    resultwindow.cpp

HEADERS  += mainwindow.h \
    boardwindow.h \
    resultwindow.h \
    state.h
