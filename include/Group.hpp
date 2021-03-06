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
	Group() : Shape() 
	{
	}
	Group(double origin_x, double origin_y) : Shape()
	{
		double* m = m_mat.data();
		m[12] = origin_x;
		m[13] = origin_y;
	}
		
	virtual ~Group()
	{
		deleteShapes();
        }

	void addShape( Shape* shape);
	void applyTransformToChildren();
	Shape* popFront();
	bool isEmpty();

        virtual void resize( double x, double y );
        void draw(bool skipColor);
	
	void translate(double x, double y);
	
	void rotate(double angle);
	
        virtual void setFillColor(const QColor& color);
        virtual void setContourColor(const QColor& color);

        virtual void setFillColorOpacity(double alpha);
        virtual void setContourColorOpacity(double alpha);

        virtual void setContourWidth(double width);

        void getBoundingBox4dv(QVector3D* b);

        void recalculateCenter();
	
	QVector2D getCenter();
	
        std::string toString();

protected:
	QLinkedList<Shape*> m_shapes;

	void deleteShapes();
	
	QVector2D rotationCenter;

};


#endif // GROUP_HPP
