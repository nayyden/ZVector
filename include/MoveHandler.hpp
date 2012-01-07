#ifndef MOVEHANDLER_HPP
#define MOVEHANDLER_HPP

#include "Handler.hpp"

class MoveHandler : public Handler
{
public:
    MoveHandler();

    virtual void resize(double, double){}
    virtual void translate(double, double);
    virtual void draw(bool skipColor);
};

#endif // MOVEHANDLER_HPP
