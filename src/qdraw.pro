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

SOURCES += main.cpp\
          qdrawmainwindow.cpp \
    glcanvas.cpp \
    Quad.cpp \
    GLDebugBufferWidget.cpp \
    Group.cpp \
    GroupManager.cpp

HEADERS  += include/qdrawmainwindow.h \
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
    include/Tools/CreateQuadTool.hpp

FORMS    += qdrawmainwindow.ui

OTHER_FILES += \
    README \
    data/main.frag.glsl \
    data/main.vert.glsl \
    ../README











































































