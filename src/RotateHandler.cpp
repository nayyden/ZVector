#include "RotateHandler.hpp"
#include "math.h"

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
                glVertex2d(20,20);
                glVertex2d(-25,-25);
                glVertex2d(15,-15);
        }
        glEnd();
        glPopMatrix();
}

void RotateHandler::translate(double x, double y)
{
        Shape::translate(x,y);
        double* mat = m_mat.data();
        QVector2D pos(mat[12],mat[13]);
        QVector2D vec1 = pos - m_shape->getCenter();
        double angle = QVector2D::dotProduct(vec1.normalized(),QVector2D(1,0));
        angle = acos(angle);
        if(pos.y()<m_shape->getCenter().y())
                angle = M_PI*2-angle;
        m_shape->rotate(angle/DEG2RAD);
}
