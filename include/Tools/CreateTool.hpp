/*  ZVector - cross platform vector drawing program using Qt and OpenGL
 *  (University project)
 *  Copyright (C) 2011  Rangel Ivanov & Nayden Dochev
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Contacts:
 *  Nayden Dochev: nayyden <at> google <dot> com
 *  Rangel Ivanov: iron_steel_88 <at> abv <dot> bg
 */

#ifndef CREATETOOL_HPP
#define CREATETOOL_HPP

#include "Tool.hpp"
#include "Quad.hpp"

class CreateTool : public Tool
{
   public:
    void handleMousePressEvent(QMouseEvent *event, GroupManager *group)
    {
        Quad* quad = new Quad(event->x(), event->y());
        quad->resize(100, 200);
        group->addShapeToNewGroup( quad );
    }
    void handleMouseReleaseEvent(QMouseEvent *event, GroupManager *group) {}
    void handleMouseMoveEvent(QMouseEvent *event, GroupManager *group) {}
};

#endif // CREATETOOL_HPP