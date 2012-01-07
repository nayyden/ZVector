#ifndef ROTATEHANDLER_HPP
#define ROTATEHANDLER_HPP

#include "Handler.hpp"

class RotateHandler : public Handler
{
public:
        RotateHandler();

        virtual void resize(double, double){}
        virtual void translate(double, double);
        virtual void draw(bool skipColor);
};

#endif // ROTATEHANDLER_HPP
