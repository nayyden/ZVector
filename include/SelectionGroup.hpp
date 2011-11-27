#ifndef SELECTIONGROUP_HPP
#define SELECTIONGROUP_HPP

#include <QMap>
#include "Group.hpp"

typedef QLinkedList<Shape*>::iterator SelectionIterator;

class SelectionGroup : public Group
{
public:
        SelectionGroup();
        virtual ~SelectionGroup();
        void addShape(Shape *shape);
        void clear();
        void draw(bool skipColor);

        bool contains(int key);
        bool empty();
        void remove(int key);

        void resize(double x, double y);
        void translate(double x, double y);

        void getBoundingBox4dv(double*);

        SelectionIterator begin();
        SelectionIterator end();
private:
};

#endif // SELECTIONGROUP_HPP
