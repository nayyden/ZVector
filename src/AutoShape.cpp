#include "include/AutoShape.hpp"
#include <GL/gl.h>
#include <math.h>

AutoShape::AutoShape(double origin_x, double origin_y, int vertices)
{
    double* m = m_mat.data();
    m[12] = origin_x;
    m[13] = origin_y;
    m_majorRadius = 0;
    m_minorRadius = 0;
    m_numberOfVertices = vertices;
}

void AutoShape::draw(bool skipColor)
{
    glPushMatrix();
    glMultMatrixd(m_mat.constData());

    if(skipColor) {
        glBegin(GL_POLYGON);
    } else {
        glBegin(GL_LINE_LOOP);
	glColor3dv(m_color);
    }

    for (int i=0; i < 360; i += (360/m_numberOfVertices)) {
        float rad = i*DEG2RAD;
        glVertex2f(cos(rad) * m_majorRadius , sin(rad) * m_minorRadius);
    }

    glEnd();
    glPopMatrix();
}

void AutoShape::resize(double x, double y)
{
    m_minorRadius += y;
    m_majorRadius += x;
}
