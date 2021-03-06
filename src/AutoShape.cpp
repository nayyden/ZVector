#include "AutoShape.hpp"
#include <GL/gl.h>
#include <math.h>
#include <limits>
#include <sstream>

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

void AutoShape::addVertices()
{
        for (float angle=-M_PI_2; angle < 2*M_PI - M_PI_2; angle += 2*M_PI/m_numberOfVertices )
        {
                m_vertices.push_back(QVector2D(cos(angle) * m_majorRadius , sin(angle) * m_minorRadius));
	}
}

void AutoShape::recalculateVertices()
{
        m_bounds[0].setX(std::numeric_limits<double>::max());
        m_bounds[0].setY(m_bounds[0].x());
        m_bounds[1].setX(-m_bounds[0].x());
        m_bounds[1].setY(m_bounds[1].x());

        for (int i=0; i < m_numberOfVertices; i ++)
        {
                float rad =  i*2*M_PI/m_numberOfVertices - M_PI_2;
		m_vertices[i].setX(cos(rad) * m_majorRadius);
		m_vertices[i].setY(sin(rad) * m_minorRadius);
                if(m_vertices[i].x() < m_bounds[0].x())
                {
                        m_bounds[0].setX(m_vertices[i].x());
                }
                if(m_vertices[i].y() < m_bounds[0].y())
                {
                        m_bounds[0].setY(m_vertices[i].y());
                }
                if(m_vertices[i].x() > m_bounds[1].x())
                {
                        m_bounds[1].setX(m_vertices[i].x());
                }
                if(m_vertices[i].y() > m_bounds[1].y())
                {
                        m_bounds[1].setY(m_vertices[i].y());
                }

	}
        m_bounds[0].setX(m_bounds[0].x() - m_contourWidth);
        m_bounds[0].setY(m_bounds[0].y() - m_contourWidth);
        m_bounds[1].setX(m_bounds[1].x() + m_contourWidth);
	m_bounds[1].setY(m_bounds[1].y() + m_contourWidth);
	
}

QVector2D AutoShape::getSize()
{
	QVector2D size;
	size.setX(m_majorRadius);
	size.setY(m_minorRadius);
	
	return size;
}

void AutoShape::setNumDetails(int details)
{
        m_vertices.clear();
        m_numberOfVertices = details;
        m_vertices.reserve(m_numberOfVertices);
        addVertices();
        recalculateNormals();
}

int AutoShape::getNumDetails()
{
        return m_numberOfVertices;
}

std::string AutoShape::toString()
{
        std::stringstream serialized;

        serialized << AUTO_SHAPE << " " << Shape::toString() << " "
                   << m_numberOfVertices << "\n";

        return serialized.str();
}
