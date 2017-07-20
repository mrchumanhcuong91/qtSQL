#-------------------------------------------------
#
# Project created by QtCreator 2017-07-12T21:09:51
#
#-------------------------------------------------

QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sql_gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    connect_db.cpp

HEADERS  += mainwindow.h \
    connect_db.h

FORMS    += mainwindow.ui
