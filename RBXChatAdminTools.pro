#-------------------------------------------------
#
# Project created by QtCreator 2014-07-29T15:24:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RBXChatAdminTools
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    modifydirdialog.cpp \
    authenticationinfo.cpp \
    baninfo.cpp \
    channelinfo.cpp \
    editchannelranklist.cpp

HEADERS  += mainwindow.h \
    modifydirdialog.h \
    authenticationinfo.h \
    baninfo.h \
    channelinfo.h \
    editchannelranklist.h

FORMS    += \
    mainwindow.ui \
    modifydirdialog.ui \
    editchannelranklist.ui
