#ifndef SELECTIONGROUP_HPP
#define SELECTIONGROUP_HPP

#include <QMap>
#include "Group.hpp"

class SelectionGroup : public Group
{
public:
        SelectionGroup();
        void addShape(int index, Shape *shape);
        void clear();
        void draw(bool skipColor);
        void resize(double x, double y);
        double* getBoundingBox();
         QMap<int,Shape*> m_shapes;
        bool contains(int key);
        void remove(int key);
private:

};

#endif // SELECTIONGROUP_HPP
