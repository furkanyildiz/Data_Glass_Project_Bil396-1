#-------------------------------------------------
#
# Project created by QtCreator
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Pong
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES +=  main.cpp\
            mainwindow.cpp \
            gameplay.cpp \
            menu.cpp\
            server.cpp \
    mythread.cpp \
    resultwindow.cpp \
    gerisayimekrani.cpp

HEADERS  += mainwindow.h \
            gameplay.h \
            menu.h\
    server.h \
    mythread.h \
    constants.h \
    resultwindow.h \
    gerisayimekrani.h

FORMS    += mainwindow.ui\
            menu.ui \
    resultwindow.ui \
    gerisayimekrani.ui

RESOURCES += \
    resources.qrc
