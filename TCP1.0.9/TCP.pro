#-------------------------------------------------
#
# Project created by QtCreator 2019-03-05T10:37:32
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TCP
TEMPLATE = app


SOURCES += main.cpp\
        serverwidget.cpp \
    clientwidget.cpp \
    student.cpp \
    pragrammer.cpp

HEADERS  += serverwidget.h \
    clientwidget.h \
    student.h \
    pragrammer.h \
    MySqlconnection.h

FORMS    += serverwidget.ui \
    clientwidget.ui
CONFIG += c++11
