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
#include <iostream>
#include <string>
#include <sstream>

Shape::Shape()
{
        m_bDrawFill = true;
        m_contourWidth = 2.f;
        m_fillColor[0] = m_fillColor[1] = m_fillColor[2] = 0.3;
        m_fillColor[3] = m_contourColor[3] = 1.0;
        m_contourColor[0] = m_contourColor[1] = m_contourColor[2] = 0.0;
        m_rotationAngle = 0;
        m_index = -1;
}

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

void Shape::setFillColorOpacity(double alpha)
{
        m_fillColor[3] = alpha;
}

void Shape::setContourColorOpacity(double alpha)
{
        m_contourColor[3] = alpha;
}

void Shape::setFillColor(const QColor& color)
{
	m_fillColor[0] = color.redF();
	m_fillColor[1] = color.greenF();
	m_fillColor[2] = color.blueF();
//        m_fillColor[3] = color.alphaF();
}

void Shape::setContourColor(const QColor& color)
{
	m_contourColor[0] = color.redF();
	m_contourColor[1] = color.greenF();
	m_contourColor[2] = color.blueF();
//        m_contourColor[3] = color.alphaF();
}

QColor Shape::getFillColor()
{
        QColor c( m_fillColor[0]*255, m_fillColor[1]*255, m_fillColor[2]*255 );
	return c;
}
QColor Shape::getContourColor()
{
        QColor c( m_contourColor[0]*255, m_contourColor[1]*255, m_contourColor[2]*255 );
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
        m_normals.push_back( ((m_vertices.last() -*it).normalized() + (*(it+1)-*it).normalized()).normalized() ) ;
        it++;
	while(it!=m_vertices.end()-1)
	{
		m_normals.push_back( ((*(it-1)-*it).normalized() + (*(it+1)-*it).normalized()).normalized() ) ;
		it++;
        }
        m_normals.push_back( ((*(it-1) - m_vertices.last()).normalized() + (m_vertices.first()-m_vertices.last()).normalized()).normalized() );
}


void Shape::draw(bool skipColor)
{
	glPushMatrix();
	glMultMatrixd(m_mat.constData());

	//calculateNormals();
	if(!skipColor)
                glColor4dv(m_fillColor);

	QList<QVector2D>::iterator it = m_vertices.begin();


        glBegin(GL_POLYGON);
        while(it != m_vertices.end())
        {
                glVertex2d(it->x(), it->y());
                it++;
        }
        glEnd();

        if(m_contourWidth) {
		if(!skipColor)
                        glColor4dv(m_contourColor);
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

void Shape::applyTransform(QMatrix4x4 &transform)
{
	m_mat = transform * m_mat;
}

void Shape::getBoundingBox4dv(QVector3D* b)
{
        b[0] = m_mat * m_bounds[0];
        b[1] = m_mat * m_bounds[1];
}

void Shape::drawBoundingBox(QVector3D* b)
{
        glLineStipple(5, 0xAAAA);
        glEnable(GL_LINE_STIPPLE);

        glBegin(GL_LINE_STRIP);
        {
                glVertex2d(b[0].x(), b[0].y());
                glVertex2d(b[1].x(), b[0].y());

                glVertex2d(b[1].x(), b[0].y());
                glVertex2d(b[1].x(), b[1].y());

                glVertex2d(b[1].x(), b[1].y());
                glVertex2d(b[0].x(), b[1].y());

                glVertex2d(b[0].x(), b[1].y());
                glVertex2d(b[0].x(), b[0].y());
        }
        glEnd();
}

double Shape::getFillOpacity()
{
        return m_fillColor[3];
}

double Shape::getContourOpacity()
{
        return m_contourColor[3];
}

void Shape::setContourWidth(double width)
{
        m_contourWidth = width;
}

float Shape::getContourWidth()
{
        return m_contourWidth;
}

void Shape::setIndex(int index)
{
        m_index = index;
}

int Shape::getIndex()
{
        return m_index;
}

void Shape::setPosition(double x, double y)
{
        double* m = m_mat.data();
        m[12] = x;
        m[13] = y;
}

std::string Shape::toString()
{
        std::stringstream serialized;


        const double* mat = m_mat.constData();

        QVector2D size = getSize();


        serialized <<  (float)mat[12] << " " << (float)mat[13] << " " // position
                    << size.x() << " " << size.y() << " "
                    << m_contourWidth << " "
                    << m_fillColor[0] << " " << m_fillColor[1] << " " << m_fillColor[2] << " " << m_fillColor[3] << " "
                    << m_contourColor[0] << " " << m_contourColor[1] << " " << m_contourColor[2] << " " << m_fillColor[3] << " "
                    << m_rotationAngle;

        return serialized.str();
}

QVector2D Shape::getSize()
{
        QVector2D size;

        double size_x = m_bounds[1].x() - m_bounds[0].x();
        double size_y = m_bounds[1].y() - m_bounds[0].y();

        size.setX(size_x);
        size.setY(size_y);

        return size;
}

void Shape::setSize(double x, double y)
{
        QVector2D size = getSize();
        double diff_x = 0, diff_y = 0;
        if(x)
        {
                diff_x = x - size.x();
        }
        if(y)
        {
                diff_y = y - size.y();
        }

        resize(diff_x, diff_y);
}
