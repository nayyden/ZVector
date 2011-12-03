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

enum SHAPETYPE
{
        QUAD,
        AUTO_SHAPE,
        GROUP,
        GROUP_TERMINATOR
};

class Shape
{
public:
        Shape();

	virtual void draw( bool skipColor = false );
	virtual void resize( double x, double y ) = 0;

	virtual void translate( double x, double y );
	virtual void rotate( double angle );
	virtual void setFillColor(double r, double g, double b);
        virtual void setFillColor(const QColor& color);

        virtual QColor getFillColor();
        virtual double getFillOpacity();
        virtual double getContourOpacity();

        virtual void setContourColor(double r, double g, double b);
        virtual void setContourColor(const QColor& color);

        virtual void setContourWidth(double width);
        virtual float getContourWidth();

        virtual void setFillColorOpacity(double alpha);
        virtual void setContourColorOpacity(double alpha);

	virtual QColor getContourColor();
        virtual double getRotationAngle();
        virtual void getBoundingBox4dv(double*);
        virtual void drawBoundingBox(double* b);

        int getIndex();
        void setIndex(int index);

        void setPosition(double x, double y);

        virtual std::string toString();

protected:
	QList<QVector2D> m_vertices;
	QList<QVector2D> m_normals;
	QMatrix4x4 m_mat;

        double m_fillColor[4];
        double m_contourColor[4];
        double m_rotationAngle;
        double m_bounds[4];

	bool m_bDrawCountour;
	bool m_bDrawFill;
	float m_contourWidth;
        static const float DEG2RAD = 3.14159/180;
	/*
    use only when neccessary, ie the number vertices has changed
 */
	void recalculateNormals();
        int m_index; // for selection
};

#endif // SHAPE_HPP
