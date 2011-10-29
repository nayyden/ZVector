#include "include/GLDebugBufferWidget.h"

GLDebugBufferWidget::GLDebugBufferWidget(QWidget *parent)
	:QGLWidget(parent)
{

}


void GLDebugBufferWidget::initializeGL()
{
	glClearColor(1, 1, 1, 1);
}

void GLDebugBufferWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawPixels(buffer.width(), buffer.height(), GL_RGBA, GL_UNSIGNED_BYTE, buffer.bits());
}

void GLDebugBufferWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, h, 0, -1, 1); // Match qt coord origin
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GLDebugBufferWidget::drawBuffer(QImage buffer)
{
	this->buffer = buffer;
	paintGL();
	updateGL();
}
