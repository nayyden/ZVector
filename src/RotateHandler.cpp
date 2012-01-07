#include "RotateHandler.hpp"

RotateHandler::RotateHandler()
{
}

void RotateHandler::draw(bool skipColor)
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

void RotateHandler::translate(double x, double y)
{
        Shape::translate(x,y);
        m_shape->resize(x,y);
}
