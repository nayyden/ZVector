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

#include "GroupManager.hpp"
#include "Group.hpp"

GroupManager::GroupManager()
{
        m_shapes.append(new Group());
        m_currentShape = 0;
        m_currentGroup = NULL;
        m_zoomFactor = 1;
}

void GroupManager::setCurrentShape(int index)
{
        if(index > m_shapes.size())
                m_currentShape = 0;
        else
                m_currentShape = index;
}

Shape * GroupManager::getCurrentShape()
{
        return m_shapes[m_currentShape];
}

Group* GroupManager::getSelection()
{
        return &m_selectionGroup;
}

void GroupManager::popShape(unsigned int index)
{
       Shape* shape;
       QList<Shape*>::iterator it = m_shapes.begin();
       int position = 0;
       while(it != m_shapes.end()) {
               if(position == index) {
                       shape = m_shapes[position];
                       m_shapes.erase(it);
                       return;
               }
               ++it;
               ++position;
       }

}

void GroupManager::addToSelection(int index)
{
        std::cout << "Adding to selection group" << '\n';
        if(index > m_shapes.size())
        {
                m_currentShape = 0;
                m_selectionGroup.clear();
        }
        else
        {       if(!m_selectionGroup.contains(index)) {
                        m_selectionGroup.addShape(index, m_shapes[index]);
                } else {
                        m_selectionGroup.remove(index);
                }
                m_currentGroup = &m_selectionGroup;

        }
}

void GroupManager::addNewShape(Shape *shape)
{
        m_shapes.push_back(shape);
        m_currentShape = m_shapes.size() - 1;
}

void GroupManager::draw()
{
        QList<Shape*>::iterator it = m_shapes.begin();
        while( it != m_shapes.end())
        {
                if((*it) != NULL) {
                        (*it)->draw();
                }
                it++;
        }
        m_selectionGroup.draw(false);
}

void GroupManager::drawToSelectionBuffer()
{
        glDisable(GL_BLEND);
        glClear(GL_COLOR_BUFFER_BIT);
        for( int i = 0; i<m_shapes.size(); i++)
        {
                int blue = (unsigned char)i;
                int green = (unsigned char)(i >> 8);
                int red = (unsigned char)(i >> 16);

                glColor3f(red/255.f, green/255.f, blue/255.f);
                if(m_shapes[i]) {
                        m_shapes[i]->draw(true);
                }
        }
        glEnable(GL_BLEND);
}

void GroupManager::groupSelected()
{
        m_currentGroup = new Group();
        m_shapes.push_back(m_currentGroup);

        QMap<int,Shape*>::iterator it = m_selectionGroup.m_shapes.begin();

        while (it!= m_selectionGroup.m_shapes.end())
        {
                m_currentGroup->addShape(m_shapes[it.key()]);
                m_shapes[it.key()] = NULL;
                it++;
        }



        m_selectionGroup.clear();
        m_currentShape = m_shapes.size() - 1;
}

Shape * GroupManager::getShape(int index)
{
        return m_shapes[index];
}

float GroupManager::getZoomFactor()
{
        return m_zoomFactor;
}


void GroupManager::setZoomFactor(float factor)
{
        m_zoomFactor = factor;
}
