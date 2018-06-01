#-------------------------------------------------
#
# Project created by QtCreator 2017-09-24T17:07:51
#
#-------------------------------------------------

QT       += core gui webenginewidgets
QMAKE_CXXFLAGS += -Werror

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyChrome
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    webpage.cpp \
    webhistory.cpp \
    downloadmanager.cpp \
    downloaditem.cpp

HEADERS += \
        mainwindow.h \
    webpage.h \
    webhistory.h \
    downloadmanager.h \
    downloaditem.h

RESOURCES += \
    resources.qrc

DISTFILES += \
    changelog.txt \
    Readme.md
