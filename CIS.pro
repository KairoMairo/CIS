#-------------------------------------------------
#
# Project created by QtCreator 2016-06-08T18:59:53
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KIS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    productionwindow.cpp \
    administrationwindow.cpp \
    authorizationwindow.cpp \
    userwindow.cpp \
    database.cpp \
    document.cpp \
    controller.cpp \
    orderwindow.cpp \
    item.cpp \
    equipmentwindow.cpp \
    equipment.cpp \
    processing.cpp \
    part.cpp \
    productionmodel.cpp \
    modelproduction.cpp \
    choosedocument.cpp \
    user.cpp

HEADERS  += mainwindow.h \
    productionwindow.h \
    administrationwindow.h \
    authorizationwindow.h \
    userwindow.h \
    database.h \
    document.h \
    controller.h \
    orderwindow.h \
    item.h \
    equipmentwindow.h \
    equipment.h \
    processing.h \
    part.h \
    productionmodel.h \
    modelproduction.h \
    choosedocument.h \
    user.h

FORMS    += mainwindow.ui \
    productionwindow.ui \
    administrationwindow.ui \
    authorizationwindow.ui \
    userwindow.ui \
    orderwindow.ui \
    equipmentwindow.ui \
    choosedocument.ui

