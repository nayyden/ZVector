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

#include <QLinkedList>

#include "Shape.hpp"
#include <glcanvas.h>

#ifndef GROUP_HPP
#define GROUP_HPP

class GLCanvas;

class Group: public Shape
{
public:
    Group( Group* parent, GLCanvas* canvas = 0):
        m_parent(parent), m_canvas(canvas) {}
    virtual ~Group()
    {
        deleteShapes();
        deleteSubGroups();
    }

    void addShape( Shape* shape);
    Group* addShapeToNewSubgroup( Shape* shape);

    virtual void draw(){}
    virtual void resize( double x, double y ) {}

    inline Group* getMaster()
    {
        Group* tmp = this;
        while (tmp->m_parent)
            tmp = tmp->m_parent;
        return tmp;
    }
    inline GLCanvas* getCanvas()
    {
        return getMaster()->m_canvas;
    }
private:
    GLCanvas* m_canvas;
    Group* m_parent;
    QLinkedList<Group*> m_childs;
    QLinkedList<Shape*> m_shapes;

    void deleteShapes();
    void deleteSubGroups();

};

#endif // GROUP_HPP