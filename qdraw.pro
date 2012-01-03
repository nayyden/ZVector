#-------------------------------------------------
#
# Project created by QtCreator 2011-10-01T22:46:01
#
#-------------------------------------------------

QT       += core gui opengl
TARGET = qdraw
TEMPLATE = app
LIBS += -lGLU
DESTDIR = bin

INCLUDEPATH += include\
        include/Tools

OBJECTS_DIR=qdraw-objects
MOC_DIR =qdraw-objects
UI_DIR=qdraw-objects

#DEFINES += GL_GLEXT_PROTOTYPES

SOURCES += \
    src/main.cpp\
    src/qdrawmainwindow.cpp \
    src/glcanvas.cpp \
    src/Quad.cpp \
    src/GLDebugBufferWidget.cpp \
    src/Group.cpp \
    src/GroupManager.cpp \
    src/qtcolortriangle.cpp\
    src/AutoShape.cpp \
    src/Shape.cpp \
    src/Tools/SelectTool.cpp \
    src/Tools/TranslateTool.cpp \
    src/Tools/ToolFactory.cpp \
    src/Tools/ResizeTool.cpp \
	src/Tools/CreateEllipseTool.cpp \
	src/Tools/CreateQuadTool.cpp \
    src/Tools/CreateTriangleTool.cpp \
    src/SelectionGroup.cpp \
    src/Utils.cpp \
    src/Handler.cpp

HEADERS  += \
    include/qdrawmainwindow.h \
    include/glcanvas.h \
    include/Shape.hpp \
	include/AutoShape.hpp \
	include/Group.hpp \
	include/GroupManager.hpp \
	include/Quad.hpp \
	include/GLDebugBufferWidget.h \
	include/qtcolortriangle.h\
	include/Tools/ToolFactory.hpp \
	include/Tools/Tool.hpp \
	include/Tools/SelectTool.hpp \
	include/Tools/TranslateTool.hpp \
	include/Tools/ResizeTool.hpp \
	include/Tools/CreateQuadTool.hpp \
    include/Tools/CreateEllipseTool.hpp \
	include/Tools/CreateTriangleTool.hpp \
    include/SelectionGroup.hpp \
    include/Handler.hpp

FORMS    += src/qdrawmainwindow.ui

RESOURCES += icons.qrc
