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

#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <QVector2D>
#include <QMatrix4x4>
#include <QColor>
#include <QList>
#include <QLinkedList>

#include <GL/gl.h>

class Shape
{
public:
        Shape():m_bDrawCountour(true),m_bDrawFill(true),m_contourWidth(3.f)
	{
		m_fillColor[0] = m_fillColor[1] = m_fillColor[2] = 0.3;
		m_contourColor[0] = m_contourColor[1] = m_contourColor[2] = 0.0;
                m_rotationAngle = 0;
	}

	virtual void draw( bool skipColor = false );
	virtual void resize( double x, double y ) = 0;

	virtual void translate( double x, double y );
	virtual void rotate( double angle );
	virtual void setFillColor(double r, double g, double b);
	virtual void setFillColor(const QColor& color);
	virtual QColor getFillColor();

	virtual void setContourColor(double r, double g, double b);
	virtual void setContourColor(const QColor& color);
	virtual QColor getContourColor();
        virtual double getRotationAngle();

protected:
	QList<QVector2D> m_vertices;
	QList<QVector2D> m_normals;
	QMatrix4x4 m_mat;

	double m_fillColor[3];
	double m_contourColor[3];
        double m_rotationAngle;

	bool m_bDrawCountour;
	bool m_bDrawFill;
	float m_contourWidth;
        static const float DEG2RAD = 3.14159/180;

	/*
    use only when neccessary, ie the number vertices has changed
 */
	void recalculateNormals();
};

#endif // SHAPE_HPP
