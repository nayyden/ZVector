#include "SelectionGroup.hpp"
#include <limits>
SelectionGroup::SelectionGroup()
{

}

SelectionGroup::~SelectionGroup()
{
        m_shapes.clear();
}

void SelectionGroup::addShape(Shape *shape)
{
        m_shapes.push_back(shape);
}

void SelectionGroup::clear()
{
        m_shapes.clear();
}

void SelectionGroup::resize(double , double )
{

}

void SelectionGroup::getBoundingBox4dv(QVector3D* bounds )
{

        bounds[0].setX(std::numeric_limits<double>::max());
        bounds[0].setY(bounds[0].x());
        bounds[1].setX(-bounds[0].x());
        bounds[1].setY(bounds[1].x());

        QLinkedList<Shape*>::iterator it = m_shapes.begin();
        while(it != m_shapes.end())
        {
                QVector3D shapeBounds[2];
                (*it)->getBoundingBox4dv(shapeBounds);
                if(shapeBounds[0].x() < bounds[0].x())
                {
                        bounds[0].setX(shapeBounds[0].x());
                }
                if(shapeBounds[0].y() < bounds[0].y())
                {
                        bounds[0].setY(shapeBounds[0].y());
                }
                if(shapeBounds[1].x() > bounds[1].x())
                {
                        bounds[1].setX(shapeBounds[1].x());
                }
                if(shapeBounds[1].y() > bounds[1].y())
                {
                        bounds[1].setY(shapeBounds[1].y());
                }
                ++it;
        }

}

bool SelectionGroup::contains(int key)
{
        bool contains = false;
        QLinkedList<Shape*>::iterator it = m_shapes.begin();
        while(it != m_shapes.end())
        {
                int index = (*it)->getIndex();
                if( index == key)
                {
                        contains = true;
                        break;
                }
                it++;
        }
        return contains;
}

void SelectionGroup::remove(int key)
{
        QLinkedList<Shape*>::iterator it = m_shapes.begin();
        while(it != m_shapes.end())
        {
                int index = (*it)->getIndex();
                if( index == key)
                {
                        m_shapes.erase(it);
                        break;
                }
                it++;
        }
}

bool SelectionGroup::empty()
{
        return m_shapes.empty();
}

void SelectionGroup::draw(bool)
{
        glPushMatrix();
        glMultMatrixd(m_mat.constData());
        {
                QVector3D boundingBox[2];
                getBoundingBox4dv(boundingBox);
                drawBoundingBox(boundingBox);
        }
        glPopMatrix();
}

void SelectionGroup::translate(double x, double y)
{
        QLinkedList<Shape*>::iterator it = m_shapes.begin();
        while(it != m_shapes.end())
        {
                (*it)->translate(x,y);
                it++;
        }
}

SelectionIterator SelectionGroup::begin()
{
        return m_shapes.begin();
}

SelectionIterator SelectionGroup::end()
{
        return m_shapes.end();
}
