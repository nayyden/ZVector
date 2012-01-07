#include "MoveHandler.hpp"

MoveHandler::MoveHandler()
{
}

void MoveHandler::draw(bool skipColor)
{
        glPushMatrix();
        glMultMatrixd(m_mat.constData());
        if(!skipColor)
        {
                glColor3f(0.9,0.9,0.2);
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

void MoveHandler::translate(double x, double y)
{
        Shape::translate(x,y);
        m_shape->resize(x,y);
}
