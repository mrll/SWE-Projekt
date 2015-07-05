#-------------------------------------------------
#
# Project created by QtCreator 2015-06-29T18:56:56
#
#-------------------------------------------------

QT          += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = SWE-Lasercutter-Simulation
TEMPLATE    = app

CONFIG      += c++11

# Auskommentieren um Debugkonsole zu unterdrücken
CONFIG      += console

# Unter Mac OS muss die libc++ mit eingebunden werden um <regex> zu benutzen
# Wichtig: clang benutzen / nicht g++
macx {
    QMAKE_CXXFLAGS  += -std=c++11 -stdlib=libc++ -mmacosx-version-min=10.7
    LIBS            += -stdlib=libc++ -mmacosx-version-min=10.7
} else {
    QMAKE_CXXFLAGS  += -std=c++11
}

SOURCES     +=  Source/main.cpp \
                Source/LCSEngineState.cpp \
                Source/LCSGridGraphicScene.cpp \
                Source/LCSLaser.cpp \
                Source/LCSLaserState.cpp \
                Source/LCSParser.cpp \
                Source/LCSSyntaxHighlighter.cpp \
                Source/MainWindow.cpp

HEADERS     +=  Source/LCSEngineState.h \
                Source/LCSGridGraphicScene.h \
                Source/LCSLaser.h \
                Source/LCSLaserState.h \
                Source/LCSParser.h \
                Source/LCSSyntaxHighlighter.h \
                Source/MainWindow.h

FORMS       +=  Source/MainWindow.ui
