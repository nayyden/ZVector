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

void SelectionGroup::getBoundingBox4dv( double* bounds )
{
        bounds[0] = std::numeric_limits<double>::max();
        bounds[1] = bounds[0];
        bounds[2] = std::numeric_limits<double>::min();
        bounds[3] = bounds[2];

        QLinkedList<Shape*>::iterator it = m_shapes.begin();
        while(it != m_shapes.end())
        {
                double shapeBounds[4];
                (*it)->getBoundingBox4dv(shapeBounds);

                if(shapeBounds[0] < bounds[0])
                {
                        bounds[0] = shapeBounds[0];
                }
                if(shapeBounds[1] < bounds[1])
                {
                        bounds[1] = shapeBounds[1];
                }
                if(shapeBounds[2] > bounds[2])
                {
                        bounds[2] = shapeBounds[2];
                }
                if(shapeBounds[3] > bounds[3])
                {
                        bounds[3] = shapeBounds[3];
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
                double boundingBox[4];
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
