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
CONFIG      += console

# Unter Mac OS muss die libc++ mit eingebunden werden um <regex> zu benutzen
# Wichtig: clang benutzen / nicht g++
macx {
    QMAKE_CXXFLAGS  += -std=c++11 -stdlib=libc++ -mmacosx-version-min=10.7
    LIBS            += -stdlib=libc++ -mmacosx-version-min=10.7
} else {
    QMAKE_CXXFLAGS  += -std=c++11
}

SOURCES     += main.cpp\
               MainWindow.cpp \
               LCSParser.cpp \
               LCSEngineState.cpp \
               LCSLaserState.cpp \
               LCSLaser.cpp \
               LCSSyntaxHighlighter.cpp \
               LCSGridGraphicScene.cpp

HEADERS     += MainWindow.h \
               LCSParser.h \
               LCSEngineState.h \
               LCSLaserState.h \
               LCSLaser.h \
               LCSSyntaxHighlighter.h \
               LCSGridGraphicScene.h

FORMS       += MainWindow.ui
