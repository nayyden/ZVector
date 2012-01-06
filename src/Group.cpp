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

#include "Group.hpp"
#include <limits>
#include <sstream>


void Group::deleteShapes()
{
	while( !m_shapes.empty() )
	{
		delete m_shapes.back();
		m_shapes.pop_back();
	}
}

void Group::addShape(Shape * shape)
{
	m_shapes.push_back(shape);
}

void Group::getBoundingBox4dv(QVector3D* bounds)
{
        bounds[0].setX(std::numeric_limits<double>::max());
        bounds[0].setY(bounds[0].x());
        bounds[1].setX(-bounds[0].x());
        bounds[1].setY(bounds[1].x());

        QLinkedList<Shape*>::iterator it = m_shapes.begin();
        while(it != m_shapes.end())
        {
                QVector3D shapeBounds[2];
                (*it)->getBoundingBox4dv(shapeBounds);
                if(shapeBounds[0].x() < bounds[0].x())
                {
                        bounds[0].setX(shapeBounds[0].x());
                }
                if(shapeBounds[0].y() < bounds[0].y())
                {
                        bounds[0].setY(shapeBounds[0].y());
                }
                if(shapeBounds[1].x() > bounds[1].x())
                {
                        bounds[1].setX(shapeBounds[1].x());
                }
                if(shapeBounds[1].y() > bounds[1].y())
                {
                        bounds[1].setY(shapeBounds[1].y());
                }
                ++it;
        }
	bounds[0] = m_mat * bounds[0];
        bounds[1] = m_mat * bounds[1];

}

void Group::draw(bool skipColor = false)
{
        glPushMatrix();
        glMultMatrixd(m_mat.constData());
        if(m_shapes.size())
        {
                QLinkedList<Shape*>::iterator sit = m_shapes.begin();
                while( sit != m_shapes.end())
                {
                        (*sit)->draw(skipColor);
                        sit++;
                }


        }
        glPopMatrix();

}

void Group::setFillColorOpacity(double alpha)
{
        Shape::setFillColorOpacity(alpha);
        QLinkedList<Shape*>::iterator sit = m_shapes.begin();
        while( sit != m_shapes.end())
        {
                (*sit)->setFillColorOpacity(alpha);
                sit++;
        }
}

void Group::setContourColorOpacity(double alpha)
{
        Shape::setContourColorOpacity(alpha);
        QLinkedList<Shape*>::iterator sit = m_shapes.begin();
        while( sit != m_shapes.end())
        {
                (*sit)->setContourColorOpacity(alpha);
                sit++;
        }
}

void Group::setFillColor(const QColor &color)
{
        Shape::setFillColor(color);
        QLinkedList<Shape*>::iterator sit = m_shapes.begin();
        while( sit != m_shapes.end())
        {
                (*sit)->setFillColor(color);
                sit++;
        }
}

void Group::setContourColor(const QColor &color)
{
        Shape::setContourColor(color);
        QLinkedList<Shape*>::iterator sit = m_shapes.begin();
        while( sit != m_shapes.end())
        {
                (*sit)->setContourColor(color);
                sit++;
        }
}

void Group::setContourWidth(double width)
{
        Shape::setContourWidth(width);
        QLinkedList<Shape*>::iterator sit = m_shapes.begin();
        while( sit != m_shapes.end())
        {
                (*sit)->setContourWidth(width);
                sit++;
        }
}

void Group::resize(double x, double y)
{
        QLinkedList<Shape*>::iterator sit = m_shapes.begin();
        while( sit != m_shapes.end())
        {
                (*sit)->resize(x, y);
                sit++;
        }
}

void Group::recalculateCenter()
{
        double* m = m_mat.data();
        QVector2D center;
        QVector3D bounds[2];
        getBoundingBox4dv(bounds);


        center.setX((bounds[1].x() - bounds[0].x())/2);
        center.setY((bounds[1].y() - bounds[0].y())/2);

        translate(center.x() - m[12], center.y() - m[13]);
        m[12] -= center.x();
	m[13] -= center.y();
	
}

std::string Group::toString()
{
	std::stringstream serialized;
	serialized << GROUP_SHAPE << " " << Shape::toString() << "\n";
	QLinkedList<Shape*>::iterator sit = m_shapes.begin();
        while( sit != m_shapes.end())
        {
		serialized << (*sit)->toString();
                sit++;
        }
	
	
	serialized << GROUP_TERMINATOR << "\n";
	
	return serialized.str();
}



