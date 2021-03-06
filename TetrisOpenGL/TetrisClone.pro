######################################################################
# Automatically generated by qmake (2.01a) Sun Mar 6 14:27:38 2011
######################################################################

CONFIG += console release debug
QT += core gui opengl widgets
TARGET = Tetris
TEMPLATE = app

DEPENDPATH += src
INCLUDEPATH = ../Common/ src "../glew-mingw/include"

win32 {
    LIBS += -L"..\glew-mingw\lib" -lglew32
}


# Input
HEADERS += \
    ../Common/GlFramework.h \
    ../Common/GlWindow.h \
    ../Common/LF_String.h \
    src/canvas.h \
    src/board.h \
    src/shape.h \
    src/game.h \
    src/player.h

SOURCES += \
    ../Common/GlFramework.cpp \
    ../Common/GlWindow.cpp \
    ../Common/LF_String.cpp \
    src/main.cpp \
    src/canvas.cpp \
    src/board.cpp \
    src/shape.cpp \
    src/game.cpp \
    src/player.cpp
