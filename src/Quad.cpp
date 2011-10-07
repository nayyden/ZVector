#include "include/Quad.hpp"
#include <GL/gl.h>

Quad::Quad( double origin_x, double origin_y )
{
    double* m = m_mat.data();
    m[12] = origin_x;
    m[13] = origin_y;
    m_vertices[0] = 0;
    m_vertices[1] = 0;
    m_vertices[2] = 0;
    m_vertices[3] = 0;
    m_vertices[4] = 0;
    m_vertices[5] = 0;
    m_vertices[6] = 0;
    m_vertices[7] = 0;
}

void Quad::draw()
{
    glPushMatrix();
    glMultMatrixd(m_mat.constData());
    glBegin(GL_QUADS);
    glLineWidth(2.0);
    glColor3d(0, 0, 0);
    for(int i = 0; i < 8; i+=2) {
        glVertex2dv(m_vertices + i);
    }

    glEnd();
    glPopMatrix();
}

bool Quad::contains( QVector2D point )
{

}

void Quad::resize(double x, double y)
{
    m_vertices[3] += y;
    m_vertices[4] += x;
    m_vertices[5] += y;
    m_vertices[6] += x;
}

