#include "SelectionGroup.hpp"
#include <limits>
SelectionGroup::SelectionGroup()
{

}

void SelectionGroup::addShape(int index, Shape *shape)
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
        double *boundingBox = getBoundingBox();
        drawBoundingBox(boundingBox);
        delete[] boundingBox;
        glPopMatrix();
}

void SelectionGroup::resize(double , double )
{

}

double* SelectionGroup::getBoundingBox()
{
        double* bounds = new double[4];
        bounds[0] = std::numeric_limits<double>::max();
        bounds[1] = bounds[0];
        bounds[2] = std::numeric_limits<double>::min();
        bounds[3] = bounds[2];

        QMap<int, Shape*>::iterator it = m_shapes.begin();
        while(it != m_shapes.end()) {
                double* shapeBounds = it.value()->getBoundingBox();

                if(shapeBounds[0] < bounds[0]) {
                        bounds[0] = shapeBounds[0];
                }
                if(shapeBounds[1] < bounds[1]) {
                        bounds[1] = shapeBounds[1];
                }

                if(shapeBounds[2] > bounds[2]) {
                        bounds[2] = shapeBounds[2];
                }
                if(shapeBounds[3] > bounds[3]) {
                        bounds[3] = shapeBounds[3];
                }
                ++it;
                delete[] shapeBounds;
        }

        return bounds;
}

bool SelectionGroup::contains(int key)
{
        return m_shapes.contains(key);
}

void SelectionGroup::remove(int key)
{
        m_shapes.remove(key);
}

