#ifndef AUTOSHAPE_HPP
#define AUTOSHAPE_HPP

#include "Shape.hpp"

class AutoShape : public Shape
{
public:
    AutoShape(double origin_x, double origin_y, int vertices = 360);

protected:
    void resize(double x, double y);

private:
    static const float DEG2RAD = 3.14159/180;
    int m_majorRadius;
    int m_minorRadius;
    int m_numberOfVertices;

    void addVertices();
    void recalculateVertices();
    void changeDetailsCount();
};


#endif // AUTOSHAPE_HPP
