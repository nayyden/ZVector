#include "AutoShape.hpp"
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
	for (int i=0; i < m_numberOfVertices; i ++) {
		float rad =  (360/m_numberOfVertices)*i*DEG2RAD;
		m_vertices.push_back(QVector2D(cos(rad) * m_majorRadius , sin(rad) * m_minorRadius));
	}
}

void AutoShape::recalculateVertices()
{
	for (int i=0; i < m_numberOfVertices; i ++) {
		float rad =  (360/m_numberOfVertices)*i*DEG2RAD;
		m_vertices[i].setX(cos(rad) * m_majorRadius);
		m_vertices[i].setY(sin(rad) * m_minorRadius);
	}
}



