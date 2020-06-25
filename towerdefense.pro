#-------------------------------------------------
#
# Project created by QtCreator 2020-05-30T16:50:14
#
#-------------------------------------------------

QT       += core gui
QT += multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = towerdefense
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    bullet.cpp \
    enemy_base.cpp \
    enemy_s.cpp \
    map1.cpp \
    tower.cpp \
    start_window.cpp \
    tower_s.cpp \
    bullet_s.cpp \
    enemy_bullet.cpp \
    prepare.cpp

HEADERS += \
        mainwindow.h \
    bullet.h \
    enemy_base.h \
    enemy_s.h \
    map1.h \
    tower.h \
    start_window.h \
    tower_s.h \
    bullet_s.h \
    enemy_bullet.h \
    prepare.h

FORMS += \
        mainwindow.ui \
    start_window.ui \
    prepare.ui

RESOURCES += \
    resource.qrc
