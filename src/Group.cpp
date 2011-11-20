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

double * Group::getBoundingBox()
{
        double* bounds = new double[4];
        bounds[0] = std::numeric_limits<double>::max();
        bounds[1] = bounds[0];
        bounds[2] = std::numeric_limits<double>::min();
        bounds[3] = bounds[2];

        QLinkedList<Shape*>::iterator it = m_shapes.begin();
        while(it != m_shapes.end()) {
                double* shapeBounds = (*it)->getBoundingBox();

                if(shapeBounds[0] < bounds[0]) {
                        bounds[0] = shapeBounds[0];
                }
                if(shapeBounds[1] < bounds[1]) {
                        bounds[1] = shapeBounds[1];
                }

                if(shapeBounds[2] > bounds[2]) {
                        bounds[2] = shapeBounds[2];
                }
                if(shapeBounds[3] > bounds[3]) {
                        bounds[3] = shapeBounds[3];
                }
                ++it;
                delete[] shapeBounds;
        }

        return bounds;
}

void Group::draw(bool skipColor = false)
{
        glPushMatrix();
        glMultMatrixd(m_mat.constData());
        QLinkedList<Shape*>::iterator sit = m_shapes.begin();
        while( sit != m_shapes.end())
        {
                (*sit)->draw(skipColor);
                sit++;
        }
        double *boundingBox = getBoundingBox();
        drawBoundingBox(boundingBox);
        delete[] boundingBox;

        glPopMatrix();

}

