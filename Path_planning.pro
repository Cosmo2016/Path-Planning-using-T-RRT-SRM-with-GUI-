#-------------------------------------------------
#
# Project created by QtCreator 2017-08-08T03:03:55
#
#-------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Path_planning
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

INCLUDEPATH += /usr/local/Cellar/boost/1.64.0_1/include
INCLUDEPATH += /usr/local/Cellar/ompl/1.3.0/include

SOURCES += main.cpp\
    mainwindow.cpp \
    line.cpp \
    rect.cpp \
    shape.cpp \
    paintwidget.cpp \
    ellipse.cpp \
    plan2deviroment.cpp

HEADERS  += mainwindow.h \
    line.h \
    rect.h \
    shape.h \
    paintwidget.h \
    ellipse.h \
    plan2deviroment.h

LIBS += -stdlib=libc++
CONFIG += c++11
QMAKE_CXXFLAGS += -stdlib=libc++
QMAKE_CXXFLAGS += -std=c++11

FORMS    += mainwindow.ui
