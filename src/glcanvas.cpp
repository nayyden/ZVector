/*  ZVector - cross platform vector drawing program using Qt and OpenGL
 *  (University project)
 *  Copyright (C) 2011  Rangel Ivanov & Nayden Dochev
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Contacts:
 *  Nayden Dochev: nayyden <at> google <dot> com
 *  Rangel Ivanov: iron_steel_88 <at> abv <dot> bg
 */

#include "glcanvas.h"
#include <iostream>
#include "Quad.hpp"
#include <GL/glext.h>

using namespace std;

GLCanvas::GLCanvas(QWidget *parent) : QGLWidget(parent)
{
	m_toolFactory = ToolFactory::getSingletonPtr();
	m_currentTool = m_toolFactory->getSelectTool();
	m_groupManager = new GroupManager();
}

void GLCanvas::initializeGL()
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
}

void GLCanvas::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);
	m_groupManager->draw();
}

void GLCanvas::redrawSelectionBufer()
{
	glDrawBuffer( GL_AUX0 );
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawBuffer( GL_BACK );
}

void GLCanvas::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, h, 0, -1, 1); // Match qt coord origin
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void GLCanvas::keyPressEvent(QKeyEvent*)
{
}

void GLCanvas::mouseReleaseEvent(QMouseEvent *event)
{
	m_currentTool->handleMouseReleaseEvent( event, m_groupManager );
}

void GLCanvas::mouseMoveEvent(QMouseEvent *event)
{
	m_currentTool->handleMouseMoveEvent( event, m_groupManager );
	paintGL();
	updateGL();
}

void GLCanvas::mousePressEvent(QMouseEvent *event)
{
	setAutoBufferSwap(false);

	m_currentTool->handleMousePressEvent( event, m_groupManager );

	//    glReadBuffer( GL_BACK );
	//    QImage fetchedBuffer = QGLWidget::convertToGLFormat(grabFrameBuffer());
	//    emit sendFrameBuffer(fetchedBuffer);

	setAutoBufferSwap(true);
	paintGL();
	updateGL();
}

void GLCanvas::rotateShapeByAngle(int angle)
{
        m_groupManager->getCurrentShape()->rotate(angle);
        paintGL();
        updateGL();
}




