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
#include "Shape.hpp"
#include "Group.hpp"

class GroupManager
{
public:
	GroupManager();
	virtual ~GroupManager()
	{
                QList<Shape*>::iterator it = m_shapes.begin();
		while( it != m_shapes.end())
		{
			if(*it)
				delete *it;
			it++;
		}
	}

	void setCurrentShape( int index )
	{
		if(index > m_shapes.size())
			m_currentShape = 0;
		else
			m_currentShape = index;
	}

	Shape* getCurrentShape()
	{
		return m_shapes[m_currentShape];
	}

        Shape* getShape(unsigned int index)
        {
               Shape* shape;
               QList<Shape*>::iterator it = m_shapes.begin();
               int position = 0;
               while(it != m_shapes.end()) {
                       if(position == index) {
                               shape = m_shapes[position];
                               m_shapes.erase(it);
                               return shape;
                       }
                       ++it;
                       ++position;
               }
        }


        void addShapeToGroup(int index)
        {
                if(!currentGroup) {
                        currentGroup = new Group();
                        m_shapes.push_back(currentGroup);
                }

                Shape *shape = getShape(index);
                currentGroup->addShape(shape);


        }


	void addNewShape( Shape* shape )
	{
		m_shapes.push_back(shape);
		m_currentShape = m_shapes.size() - 1;
	}

	inline void draw()
	{
                QList<Shape*>::iterator it = m_shapes.begin();
		while( it != m_shapes.end())
		{
			(*it)->draw();
			it++;
		}
	}

	inline void drawToSelectionBuffer()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		for( int i = 0; i<m_shapes.size(); i++)
		{
			int blue = (unsigned char)i;
			int green = (unsigned char)(i >> 8);
			int red = (unsigned char)(i >> 16);

			glColor3f(red/255.f, green/255.f, blue/255.f);

			m_shapes[i]->draw(true);
		}
	}

private:
        QList<Shape*> m_shapes;
        Group *currentGroup;
	int m_currentShape;
};

#endif // GROUPMANAGER_HPP
