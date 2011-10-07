#ifndef QUAD_HPP
#define QUAD_HPP

#include "Shape.hpp"

class Quad : public Shape
{
public:
    Quad( double origin_x, double origin_y );
    ~Quad();

    void draw();
    void resize(double x, double y);
    bool contains( QVector2D point );

private:
    double m_vertices[8];

};

#endif // QUAD_HPP
