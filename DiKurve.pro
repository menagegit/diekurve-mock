#-------------------------------------------------
#
# Project created by QtCreator 2014-04-11T18:56:10
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = DiKurve
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    point_joueur.cpp \
    remote_player.cpp \
    game_area.cpp \
    game_status.cpp \
    game_view.cpp \
    geometry.cpp \
    keyboard_handler.cpp

HEADERS  += mainwindow.h \
    remote_player.hpp \
    game_area.hpp \
    game_status.hpp \
    game_view.hpp \
    geometry.hpp \
    keyboard_handler.hpp \
    point_joueur.hpp

FORMS    += mainwindow.ui
