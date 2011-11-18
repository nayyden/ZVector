#ifndef SELECTIONGROUP_HPP
#define SELECTIONGROUP_HPP

#include <QMap>
#include "Group.hpp"

class SelectionGroup : public Group
{
public:
        SelectionGroup();
        void addShape(Shape *shape, int index);
        void clear();
        void draw(bool skipColor);
        void resize(double x, double y);

private:
        QMap<int,Shape*> m_shapes;
};

#endif // SELECTIONGROUP_HPP
