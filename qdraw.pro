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

#DEFINES += GL_GLEXT_PROTOTYPES

SOURCES += \
    src/main.cpp\
    src/qdrawmainwindow.cpp \
    src/glcanvas.cpp \
    src/Quad.cpp \
    src/GLDebugBufferWidget.cpp \
    src/Group.cpp \
    src/GroupManager.cpp \
    src/qtcolortriangle.cpp

HEADERS  += \
    include/qdrawmainwindow.h \
    include/glcanvas.h \
    include/Shape.hpp \
    include/Quad.hpp \
    include/Tools/SelectTool.hpp \
    include/Tools/ResizeTool.hpp \
    include/Tools/Tool.hpp \
    include/Tools/ToolFactory.hpp \
    include/GLDebugBufferWidget.h \
    include/Group.hpp \
    include/Tools/CreateTool.hpp \
    include/GroupManager.hpp \
    include/Tools/CreateQuadTool.hpp \
    include/Tools/TranslateTool.hpp \
    include/qtcolortriangle.h

FORMS    += src/qdrawmainwindow.ui

RESOURCES += icons.qrc



















































































