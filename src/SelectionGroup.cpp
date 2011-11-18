#include "SelectionGroup.hpp"

SelectionGroup::SelectionGroup()
{

}

void SelectionGroup::addShape(Shape *shape, int index)
{
        m_shapes[index] = shape;
}

void SelectionGroup::clear()
{
        m_shapes.clear();
}

void SelectionGroup::draw(bool skipColor)
{
        glPushMatrix();
        glMultMatrixd(m_mat.constData());
        QMap<int,Shape*>::iterator sit = m_shapes.begin();
        while( sit != m_shapes.end())
        {
                sit.value()->draw(skipColor);
                sit++;
        }
        glPopMatrix();
}

void SelectionGroup::resize(double , double )
{

}
