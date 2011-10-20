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

#ifndef GROUP_HPP
#define GROUP_HPP

#include <QLinkedList>
#include <GL/gl.h>

#include "Shape.hpp"

class Group: public Shape
{
public:
    virtual ~Group()
    {
        deleteShapes();
    }

    void addShape( Shape* shape);

    virtual void resize( double x, double y ) {}

    inline void draw(bool skipColor = false)
    {
        QLinkedList<Shape*>::iterator sit = m_shapes.begin();
        while( sit != m_shapes.end())
        {
            (*sit)->draw(skipColor);
            sit++;
        }
    }

    void translate(double x, double y);

private:
    QLinkedList<Shape*> m_shapes;

    void deleteShapes();

};

#endif // GROUP_HPP
