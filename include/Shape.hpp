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
class Shape
{
public:
    Shape(){ m_color[0] = m_color[1] = m_color[2] = 0.3; }
    virtual void draw( bool skipColor = false ) = 0;
    //virtual bool contains( QVector2D point ) = 0;
    virtual void resize( double x, double y ) = 0;

    virtual void translate( double x, double y )
    {
        double* m = m_mat.data();
        m[12] += x;
        m[13] += y;
    }

    virtual void rotate( double angle )
    {

    }

    virtual void setColor(double r, double g, double b)
    {
        m_color[0] = r;
        m_color[1] = g;
        m_color[2] = b;
    }

    virtual void setColor(const QColor& color)
    {
        m_color[0] = color.redF();
        m_color[1] = color.greenF();
        m_color[2] = color.blueF();
    }

    virtual QColor getColor()
    {
        QColor c(
                    m_color[0]*255,
                    m_color[1]*255,
                    m_color[2]*255
                    );
        return c;
    }

protected:
    QMatrix4x4 m_mat;
    double m_color[3];
};

#endif // SHAPE_HPP
