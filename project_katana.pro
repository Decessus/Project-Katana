#-------------------------------------------------
#
# Project created by QtCreator 2011-09-04T15:59:58
#
#-------------------------------------------------

QT       += core gui network xml webkit

TARGET = project_katana
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    webframe.cpp \
    tabbutton.cpp \
    3rdParty/googlesuggest.cpp \
    settingsdialog.cpp

HEADERS  += mainwindow.h \
    webframe.h \
    tabbutton.h \
    3rdParty/googlesuggest.h \
    settingsdialog.h

FORMS    += mainwindow.ui \
    settingsdialog.ui

RESOURCES += \
    icons.qrc
