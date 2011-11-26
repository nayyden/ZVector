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

#include "SelectTool.hpp"
#include <iostream>
#include "Group.hpp"
#include "GroupManager.hpp"


void SelectTool::handleMousePressEvent(QMouseEvent *event, GroupManager *group)
{
        if(event->modifiers() == Qt::ControlModifier) {

                group->drawToSelectionBuffer();

                glReadBuffer( GL_BACK);
                GLint viewport[4];
                glGetIntegerv(GL_VIEWPORT, viewport);
                unsigned char pixels[4];
                glReadPixels(event->x(),viewport[3] - event->y(),1,1,GL_RGBA,GL_UNSIGNED_BYTE,(void*)pixels);

                int index = 256*256*pixels[0] + 256*pixels[1] + pixels[2];

                group->addToSelection(index);
                std::cout << "Added to group" << '\n';
        } else {
                group->drawToSelectionBuffer();

                glReadBuffer(GL_BACK);
                GLint viewport[4];
                glGetIntegerv(GL_VIEWPORT, viewport);
                unsigned char pixels[4];
                glReadPixels(event->x(),viewport[3] - event->y(),1,1,GL_RGBA,GL_UNSIGNED_BYTE,(void*)pixels);

                int index = 256*256*pixels[0] + 256*pixels[1] + pixels[2];
                std::cout << index << '\n';

                group->setCurrentShape(index);
                emit shapeChanged(group->getCurrentShape());
        }
}

void SelectTool::handleMouseReleaseEvent(QMouseEvent *, GroupManager *)
{
}

void SelectTool::handleMouseMoveEvent(QMouseEvent *, GroupManager *)
{
}
