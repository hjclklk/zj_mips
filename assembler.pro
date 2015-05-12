#-------------------------------------------------
#
# Project created by QtCreator 2015-04-19T20:37:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = assembler
TEMPLATE = app
CONFIG+=debug

SOURCES += main.cpp\
        mainwindow.cpp \
    memorymanageunit.cpp \
    mipscpu.cpp \
    cpu.cpp \
    binary.cpp

HEADERS  += mainwindow.h \
    memorymanageunit.h \
    mipscpu.h \
    cpu.h \
    binary.h

FORMS    += mainwindow.ui \
    cpu.ui
