#-------------------------------------------------
#
# Project created by QtCreator 2019-03-05T10:37:32
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TCP
TEMPLATE = app


SOURCES += main.cpp\
        serverwidget.cpp \
    clientwidget.cpp \
    student.cpp \
    pragrammer.cpp \
    xml.cpp

HEADERS  += serverwidget.h \
    clientwidget.h \
    student.h \
    pragrammer.h \
    xml.h

FORMS    += serverwidget.ui \
    clientwidget.ui
CONFIG += c++11

DISTFILES += \
    xml.xml
