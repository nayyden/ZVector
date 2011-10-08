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

#include "include/glcanvas.h"
#include <iostream>
#include "Quad.hpp"
#include <GL/glext.h>

using namespace std;

GLCanvas::GLCanvas(QWidget *parent) : QGLWidget(parent)
{
}

void GLCanvas::initializeGL()
{
    glClearColor(1, 1, 1, 1);
    glDrawBuffer(GL_FRONT );
}

void GLCanvas::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    QLinkedList<Shape*>::iterator it = m_shapes.begin();
    while( it !=  m_shapes.end() )
    {
        (*it)->draw();
        it++;
    }
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

void GLCanvas::keyPressEvent(QKeyEvent *e)
{

}

void GLCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    releaseMouse();
    m_current = 0;
}

void GLCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if( m_current ) {
        double dx = event->x() - m_mousePos.x();
        double dy = event->y() - m_mousePos.y();
        m_current->resize( dx, dy );
        m_mousePos.setX( event->x() );
        m_mousePos.setY( event->y() );
        paintGL();
        updateGL();
    }
}

void GLCanvas::mousePressEvent(QMouseEvent *event)
{

    grabMouse();
    m_mousePos.setX( event->x() );
    m_mousePos.setY( event->y() );

    m_current = new Quad(event->x(), event->y());
    m_shapes.push_back(m_current);
    paintGL();
    updateGL();
}


