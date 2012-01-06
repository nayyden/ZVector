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

#ifndef GROUPMANAGER_HPP
#define GROUPMANAGER_HPP

#include <GL/gl.h>
#include <iostream>

#include "Shape.hpp"
#include "SelectionGroup.hpp"
#include "Handler.hpp"

class GroupManager
{
public:
        GroupManager();

        virtual ~GroupManager();

        void setCurrentShape( int index );

        Shape* getCurrentShape();

        void popShape(unsigned int index);

        void addToSelection(int index);

        void addNewShape( Shape* shape );

        void draw();

        void drawToSelectionBuffer();

        void setZoomFactor(float factor);

        float getZoomFactor();

        void groupSelected();

        Shape *getShape(int index);

        void clearSelection();

        void moveCurrentShapeBack();

        void moveCurrentShapeFront();

        void saveToFile(std::string filename);

        void restoreFromFile(std::string filename);
	
	void restoreGroup(std::ifstream &file, Group* group, int type);
	
	void collapseSelectedGroup();

private:
        QList<Shape*> m_shapes;
        int m_currentShape;
        SelectionGroup m_selectionGroup;
        float m_zoomFactor;
        Handler* m_handler;
};

#endif // GROUPMANAGER_HPP
