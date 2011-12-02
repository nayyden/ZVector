#ifndef HANDLER_HPP
#define HANDLER_HPP

#include "Shape.hpp"

class Handler : public Shape
{
public:
    Handler();
    void setShape(Shape* shape){m_shape = shape;}
    virtual void draw(bool skipColor);
    virtual void resize(double, double){}
    virtual void translate(double x, double y);

    void setSize(double size);

private:
    Shape* m_shape;
    double m_size;
};

#endif // HANDLER_HPP
