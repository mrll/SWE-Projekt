#-------------------------------------------------
#
# Project created by QtCreator 2015-05-23T20:10:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LaserSim
TEMPLATE = app


SOURCES += \
    Source/Controller/LCController.cpp \
    Source/Model/LCLaser.cpp \
    Source/Model/LCParser.cpp \
    Source/Model/LCState.cpp \
    Source/View/LCGridGraphicScene.cpp \
    Source/View/LCSyntaxHighlighter.cpp \
    Source/View/LCUserInterface.cpp \
    Source/main.cpp

HEADERS  += \
    Source/Controller/LCController.h \
    Source/Model/LCLaser.h \
    Source/Model/LCParser.h \
    Source/Model/LCState.h \
    Source/View/LCGridGraphicScene.h \
    Source/View/LCSyntaxHighlighter.h \
    Source/View/LCUI_Base.h \
    Source/View/LCUserInterface.h

FORMS    += \
    LaserSim.ui
