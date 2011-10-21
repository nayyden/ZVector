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
#include <Group.hpp>

#include <iostream>

class GroupManager
{
public:
    GroupManager();
    virtual ~GroupManager()
    {
        QList<Group*>::iterator it = m_groups.begin();
        while( it != m_groups.end())
        {
            if(*it)
                delete *it;
            it++;
        }
    }

    void setCurrentGroup( unsigned int index )
    {
        if(index > m_groups.size())
            m_currentGroup = 0;
        else
            m_currentGroup = index;
    }

    Group* getCurrentGroup()
    {
        return m_groups[m_currentGroup];
    }

    void addShapeToCurrentGroup( Shape* shape )
    {
        m_groups[m_currentGroup]->addShape(shape);
    }

    void addShapeToNewGroup( Shape* shape )
    {
        m_groups.push_back(new Group);
        m_currentGroup = m_groups.size() - 1;
        m_groups.back()->addShape(shape);
    }

    inline void draw()
    {
        QList<Group*>::iterator it = m_groups.begin();
        while( it != m_groups.end())
        {
            (*it)->draw();
            it++;
        }
    }

    inline void drawToSelectionBuffer()
    {
        //glDrawBuffer( GL_LEFT );
        glClear(GL_COLOR_BUFFER_BIT);
        for( int i = 0; i<m_groups.size(); i++)
        {
            int blue = (unsigned char)i;
            int green = (unsigned char)(i >> 8);
            int red = (unsigned char)(i >> 16);

            glColor3f(red/255.f, green/255.f, blue/255.f);

            m_groups[i]->draw(true);
        }
        //glDrawBuffer(GL_BACK);
    }

private:
    QList<Group*> m_groups;
    unsigned int m_currentGroup;
};

#endif // GROUPMANAGER_HPP
