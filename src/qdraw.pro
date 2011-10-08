#-------------------------------------------------
#
# Project created by QtCreator 2011-10-01T22:46:01
#
#-------------------------------------------------

QT       += core gui opengl
TARGET = qdraw
TEMPLATE = app

DESTDIR = ../bin

INCLUDEPATH += include

OBJECTS_DIR=../qdraw-objects
MOC_DIR =../qdraw-objects
UI_DIR=../qdraw-objects


SOURCES += main.cpp\
          qdrawmainwindow.cpp \
    glcanvas.cpp \
    Quad.cpp

HEADERS  += include/qdrawmainwindow.h \
            include/glcanvas.h \
    include/Shape.hpp \
    include/Quad.hpp

FORMS    += qdrawmainwindow.ui

OTHER_FILES += \
    README


















