#-------------------------------------------------
#
# Project created by QtCreator 2010-11-24T22:36:07
#
#-------------------------------------------------

QT -= core gui

TARGET = network
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += d:/work/solutions/elib/include

SOURCES += main.cpp

LIBS += -lwsock32
#-lws2_32
