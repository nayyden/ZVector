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

#include "Shape.hpp"
#include <math.h>

void Shape::translate( double x, double y )
{
	double* m = m_mat.data();
	m[12] += x;
	m[13] += y;
}

void Shape::rotate(double  angle)
{
        m_rotationAngle = angle;
        double radians = angle * DEG2RAD;
        double* m = m_mat.data();

        m[0] = cos(radians);
        m[1] = -sin(radians);
        m[4] = sin(radians);
        m[5] = cos(radians);
}

double Shape::getRotationAngle()
{
        return m_rotationAngle;
}

void Shape::setFillColor(double r, double g, double b)
{
	m_fillColor[0] = r;
	m_fillColor[1] = g;
	m_fillColor[2] = b;
}


void Shape::setContourColor(double r, double g, double b)
{
	m_contourColor[0] = r;
	m_contourColor[1] = g;
	m_contourColor[2] = b;
}

void Shape::setFillColor(const QColor& color)
{
	m_fillColor[0] = color.redF();
	m_fillColor[1] = color.greenF();
	m_fillColor[2] = color.blueF();
}

void Shape::setContourColor(const QColor& color)
{
	m_contourColor[0] = color.redF();
	m_contourColor[1] = color.greenF();
	m_contourColor[2] = color.blueF();
}

QColor Shape::getFillColor()
{
	QColor c(
				m_fillColor[0]*255,
				m_fillColor[1]*255,
				m_fillColor[2]*255
				);
	return c;
}
QColor Shape::getContourColor()
{
	QColor c(
				m_contourColor[0]*255,
				m_contourColor[1]*255,
				m_contourColor[2]*255
				);
	return c;
}

// private
void Shape::recalculateNormals()
{
	if(m_normals.size()>0)
	{
		m_normals.erase(m_normals.begin(), m_normals.end());
	}
	QList<QVector2D>::iterator it = m_vertices.begin();
	it++;
	m_normals.push_back( ((*(it-1)-*it).normalized() + (*(it+1)-*it).normalized()).normalized() ) ;
	m_normals.push_back(m_normals.first());
	it++;
	while(it!=m_vertices.end()-1)
	{
		m_normals.push_back( ((*(it-1)-*it).normalized() + (*(it+1)-*it).normalized()).normalized() ) ;
		it++;
	}
	m_normals.push_back(m_normals.last());
}


void Shape::draw(bool skipColor)
{
	glPushMatrix();
	glMultMatrixd(m_mat.constData());

	//calculateNormals();
	if(!skipColor)
		glColor3dv(m_fillColor);

	QList<QVector2D>::iterator it = m_vertices.begin();

	if(m_bDrawFill) {
		glBegin(GL_POLYGON);
		while(it != m_vertices.end())
		{
			glVertex2d(it->x(), it->y());
			it++;
		}
		glEnd();
	}
	if(m_bDrawCountour) {
		if(!skipColor)
			glColor3dv(m_contourColor);
		it = m_vertices.begin();
		glBegin(GL_QUADS);
		int i = 0;
		while(it != m_vertices.end()-1)
		{
			QVector2D tmp(*it - m_normals[i]*m_contourWidth );
			glVertex2d(tmp.x(), tmp.y());
			glVertex2d((it)->x(), (it)->y());
			glVertex2d((it+1)->x(), (it+1)->y());
			tmp =*(it+1) - m_normals[i+1]*m_contourWidth;
			glVertex2d(tmp.x(), tmp.y());
			it++;
			i++;
		}
		// close with the first
		QVector2D tmp(*it - m_normals[i]*m_contourWidth );
		glVertex2d(tmp.x(), tmp.y());
		glVertex2d((it)->x(), (it)->y());
		glVertex2d(m_vertices[0].x(), m_vertices[0].y());
		tmp = m_vertices[0] - m_normals[0]*m_contourWidth;
		glVertex2d(tmp.x(), tmp.y());

		glEnd();
	}

	glPopMatrix();
}

double * Shape::getBoundingBox()
{
        double* m = m_mat.data();
        double* globalBounds = new double[4];
        globalBounds[0] = m_bounds[0] + m[12];
        globalBounds[1] = m_bounds[1] + m[13];
        globalBounds[2] = m_bounds[2] + m[12];
        globalBounds[3] = m_bounds[3] + m[13];

        return globalBounds;
}
