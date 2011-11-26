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
        m_x = 0;
        m_y = 0;
        m_zoom = 1;
}

void GLCanvas::initializeGL()
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
        glEnable( GL_POLYGON_SMOOTH );
        glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
        m_width = w;
        m_height = h;
        applyViewportTransform();
}

void GLCanvas::keyPressEvent(QKeyEvent*)
{
}

void GLCanvas::mouseReleaseEvent(QMouseEvent *event)
{
        if(event->button() == Qt::LeftButton)
        {
                leftButtonPressed = false;
        }
        else if(event->button() == Qt::MiddleButton)
        {
                middleButtonPressed = false;
        }
        m_currentTool->handleMouseReleaseEvent( event, m_groupManager );
        m_diff.x = 0;
        m_diff.y = 0;
}

void GLCanvas::mouseMoveEvent(QMouseEvent *event)
{
        if(leftButtonPressed)
        {
                m_currentTool->handleMouseMoveEvent( event, m_groupManager );
                paintGL();
                updateGL();
        }
        else if(middleButtonPressed)
        {
                double dx = event->x() - m_diff.x;
                double dy = event->y() - m_diff.y;

                m_x -= dx*m_zoom;
                m_y -= dy*m_zoom;
                applyViewportTransform();

                m_diff.x = event->x();
                m_diff.y = event->y();
        }

}

void GLCanvas::mousePressEvent(QMouseEvent *event)
{
        if(event->button() == Qt::LeftButton)
        {
                leftButtonPressed = true;
        }
        else if(event->button() == Qt::MiddleButton)
        {
                middleButtonPressed = true;
        }

        if(leftButtonPressed)
        {
                setAutoBufferSwap(false);

                m_currentTool->handleMousePressEvent( event, m_groupManager );

                setAutoBufferSwap(true);
                paintGL();
                updateGL() ;
        }
        else
        {
                m_diff.x = event->x();
                m_diff.y = event->y();
        }
}

void GLCanvas::rotateShapeByAngle(int angle)
{
        m_groupManager->getCurrentShape()->rotate(angle);
        paintGL();
        updateGL();
}

void GLCanvas::groupSelectedShapes()
{
        m_groupManager->groupSelected();
}

void GLCanvas::applyViewportTransform()
{
        glViewport(0,0,m_width, m_height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho( -m_width*m_zoom/2+m_x, m_width*m_zoom/2+m_x, m_height*m_zoom/2+m_y, -m_height*m_zoom/2+m_y, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        paintGL();
        updateGL();
}

void GLCanvas::wheelEvent(QWheelEvent *e)
{
        if(e->delta()<0)
        {
                m_zoom *= 1.1;
        }
        else
        {
                m_zoom /= 1.1;
        }
        m_groupManager->setZoomFactor(m_zoom);
        applyViewportTransform();
}




