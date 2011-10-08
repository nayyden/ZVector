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

#ifndef GLCANVAS_H
#define GLCANVAS_H

#include <QGLWidget>
#include <QMouseEvent>
#include "Shape.hpp"
#include <QLinkedList>

enum QDRAW_TOOL{
    QDRAW_TOOL_CREATE,
    QDRAW_TOOL_TRANSLATE,
    QDRAW_TOOL_RESIZE
};

class GLCanvas : public QGLWidget
{

    Q_OBJECT
public:
    explicit GLCanvas(QWidget *parent = 0);
    virtual ~GLCanvas()
    {
        QLinkedList<Shape*>::iterator it = m_shapes.begin();
        while( it !=  m_shapes.end() )
        {
            delete *it;
            it++;
        }
    }

signals:

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *e);

    void mouseReleaseEvent(QMouseEvent *event );
    void mouseMoveEvent(QMouseEvent * event );

public slots:

private:
    struct point
    {
        double x;
        double y;
    };

    QList<point> vertexList;
    QLinkedList<Shape*> m_shapes;
    Shape* m_current;
    QVector2D m_mousePos;
    QDRAW_TOOL m_currentTool;
};



#endif // GLCANVAS_H
