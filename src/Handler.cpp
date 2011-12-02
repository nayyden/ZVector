#include "Handler.hpp"

#include <GL/gl.h>

Handler::Handler()
{
}

void Handler::draw(bool skipColor)
{
        glPushMatrix();
        glMultMatrixd(m_mat.constData());
        if(!skipColor)
        {
                glColor3f(0.3,0.1,0.6);
        }
        glBegin(GL_TRIANGLES);
        {
                glVertex2d(5,5);
                glVertex2d(-5,-5);
                glVertex2d(10,-10);
        }
        glEnd();
        glPopMatrix();
}

void Handler::translate(double x, double y)
{
        Shape::translate(x,y);
        m_shape->resize(x,y);
}

void Handler::setSize(double size)
{
        m_size = size;
}
