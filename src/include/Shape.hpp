#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <QVector2D>
#include <QMatrix4x4>
class Shape
{
public:
    virtual void draw() = 0;
    virtual bool contains( QVector2D point ) = 0;
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


protected:
    QMatrix4x4 m_mat;
};

#endif // SHAPE_HPP
