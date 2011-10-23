#ifndef CREATEELLIPSETOOL_HPP
#define CREATEELLIPSETOOL_HPP
#include "Tool.hpp"
#include "AutoShape.hpp"

class CreateEllipseTool : public Tool
{
public:
    void handleMousePressEvent(QMouseEvent *event, GroupManager *group)
    {
        AutoShape *autoShape = new AutoShape(event->x(), event->y());
        group->addShapeToNewGroup(autoShape);
    }

    void handleMouseReleaseEvent(QMouseEvent *event, GroupManager *group)
    {
        m_diff.x = 0.0;
        m_diff.y = 0.0;
    }

    void handleMouseMoveEvent(QMouseEvent *event, GroupManager *group)
    {
        double dx;
        double dy;
        if(m_diff.x == 0 && m_diff.y == 0) {
            dx = 0;
            dy = 0;
        } else {
            dx = event->x() - m_diff.x;
            dy = event->y() - m_diff.y;
        }

        group->getCurrentGroup()->resize( dx, dy );
        m_diff.x = event->x();
        m_diff.y = event->y();
    }
};

#endif // CREATEELLIPSETOOL_HPP
