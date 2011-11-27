#ifndef CREATEELLIPSETOOL_HPP
#define CREATEELLIPSETOOL_HPP
#include "Tool.hpp"
#include "AutoShape.hpp"

class CreateEllipseTool : public Tool
{
public:
	void handleMousePressEvent(QMouseEvent *event, GroupManager *group);
	void handleMouseReleaseEvent(QMouseEvent*, GroupManager*);
	void handleMouseMoveEvent(QMouseEvent *event, GroupManager *group);
};

#endif // CREATEELLIPSETOOL_HPP
