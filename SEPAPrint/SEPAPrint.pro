#-------------------------------------------------
#
# Project created by QtCreator 2015-05-27T12:43:50
#
#-------------------------------------------------

QT       += core gui printsupport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SEPAPrint
TEMPLATE = app
RC_ICONS = icons/sepaprint.ico


SOURCES += main.cpp\
        mainwindow.cpp \
    about.cpp \
    dialogsettings.cpp

HEADERS  += mainwindow.h \
    about.h \
    dialogsettings.h

FORMS    += mainwindow.ui \
    about.ui \
    dialogsettings.ui

RESOURCES += \
    images.qrc
