#-------------------------------------------------
#
# Project created by QtCreator 2015-09-15T22:40:24
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PDFI_Data
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    odbcconnect.cpp

HEADERS  += mainwindow.h \
    databaseconnect.h \
    odbcconnect.h

FORMS    += mainwindow.ui

RESOURCES +=
