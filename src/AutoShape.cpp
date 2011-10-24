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
    m_vertices.reserve(m_numberOfVertices);
    addVertices();
    recalculateNormals();
}

void AutoShape::draw(bool skipColor)
{
    glPushMatrix();
    glMultMatrixd(m_mat.constData());

    //calculateNormals();
    if(!skipColor)
	    glColor3dv(m_fillColor);

    QList<QVector2D>::iterator it = m_vertices.begin();

    if(m_bDrawFill) {
	    glBegin(GL_POLYGON);
	    while(it != m_vertices.end())
	    {
		    glVertex2d(it->x(), it->y());
		    it++;
	    }
	    glEnd();
    }
    if(m_bDrawCountour) {
	    glColor3dv(m_contourColor);
	    it = m_vertices.begin();
	    glBegin(GL_QUADS);
	    int i = 0;
	    while(it != m_vertices.end()-1)
	    {
		    QVector2D tmp(*it - m_normals[i]*m_contourWidth );
		    glVertex2d(tmp.x(), tmp.y());
		    glVertex2d((it)->x(), (it)->y());
		    glVertex2d((it+1)->x(), (it+1)->y());
		    tmp =*(it+1) - m_normals[i+1]*m_contourWidth;
		    glVertex2d(tmp.x(), tmp.y());
		    it++;
		    i++;
	    }
	    // close with the first
	    QVector2D tmp(*it - m_normals[i]*m_contourWidth );
	    glVertex2d(tmp.x(), tmp.y());
	    glVertex2d((it)->x(), (it)->y());
	    glVertex2d(m_vertices[0].x(), m_vertices[0].y());
	    tmp = m_vertices[0] - m_normals[0]*m_contourWidth;
	    glVertex2d(tmp.x(), tmp.y());

	    glEnd();
    }

    glPopMatrix();
}



void AutoShape::resize(double x, double y)
{
    m_minorRadius += y;
    m_majorRadius += x;
    recalculateVertices();
    recalculateNormals();
}

void AutoShape::changeDetailsCount()
{
}

void AutoShape::addVertices()
{
	for (int i=0; i < m_numberOfVertices; i += (360/m_numberOfVertices)) {
		float rad = i*DEG2RAD;
		m_vertices.push_back(QVector2D(cos(rad) * m_majorRadius , sin(rad) * m_minorRadius));
	}
}

void AutoShape::recalculateVertices()
{
	for (int i=0; i < m_numberOfVertices; i += (360/m_numberOfVertices)) {
		float rad = i*DEG2RAD;
		m_vertices[i].setX(cos(rad) * m_majorRadius);
		m_vertices[i].setY(sin(rad) * m_minorRadius);
	}
}



