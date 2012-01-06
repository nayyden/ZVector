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

#include <fstream>
#include <iostream>
#include "GroupManager.hpp"
#include "Group.hpp"
#include "Quad.hpp"

GroupManager::GroupManager()
{
        m_shapes.append(new Group());
        m_shapes.append(new Handler());
        m_handler = (Handler*)m_shapes[1];
        m_currentShape = 0;
        m_zoomFactor = 1;
}

GroupManager::~GroupManager()
{
        QList<Shape*>::iterator it = m_shapes.begin();
        while( it != m_shapes.end())
        {
                if(*it)
                {
                        delete *it;
                }
                it++;
        }
}

void GroupManager::setCurrentShape(int index)
{
        if(index > m_shapes.size())
        {
                clearSelection();
        }
        else
        {
                if(index == 1)
                {
                        m_handler->setShape(m_shapes[m_currentShape]);
                }
                m_currentShape = index;
                if(!m_selectionGroup.contains(index))
                {
                        m_selectionGroup.clear();
                }
        }
}

Shape * GroupManager::getCurrentShape()
{
        if(m_selectionGroup.empty())
        {
                return m_shapes[m_currentShape];
        }
        else
        {
                return &m_selectionGroup;
        }
}

void GroupManager::popShape(unsigned int index)
{
       Shape* shape;
       QList<Shape*>::iterator it = m_shapes.begin();
       int position = 0;
       while(it != m_shapes.end())
       {
               if(position == index)
               {
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
        if(index > m_shapes.size())
        {
                clearSelection();
        }
        else
        {
                if(!m_selectionGroup.contains(index))
                {
                        m_shapes[index]->setIndex(index);
                        m_selectionGroup.addShape(m_shapes[index]);
                } else
                {
                        m_selectionGroup.remove(index);
                }
        }
}

void GroupManager::addNewShape(Shape *shape)
{
        m_shapes.push_back(shape);
        m_currentShape = m_shapes.size() - 1;
}

void GroupManager::draw()
{
        QList<Shape*>::iterator it = m_shapes.begin()+2;
        while( it != m_shapes.end())
        {
                if((*it) != NULL) {
                        (*it)->draw();
                }
                it++;
        }
        if(m_currentShape)
        {
                QVector3D bb[2];
                m_shapes[m_currentShape]->getBoundingBox4dv(bb);
                m_handler->setPosition(bb[1].x(), bb[1].y());
                m_handler->draw(false);
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
        Group* group = new Group();
        m_shapes.push_back(group);

        SelectionIterator it = m_selectionGroup.begin();
        while (it!= m_selectionGroup.end())
        {
                group->addShape(m_shapes[(*it)->getIndex()]);
                m_shapes[(*it)->getIndex()] = NULL;
                it++;
        }
        group->recalculateCenter();
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

void GroupManager::clearSelection()
{
        m_currentShape = 0;
        m_selectionGroup.clear();
}

void GroupManager::moveCurrentShapeBack()
{
       int previousShape = m_currentShape - 1;
       while(previousShape >= 1) {
               if(m_shapes[previousShape]) {
                       m_shapes.swap(m_currentShape, previousShape);
                       m_currentShape = previousShape;
                       break;
               }
               --previousShape;
       }
}

void GroupManager::moveCurrentShapeFront()
{
        int nextShape = m_currentShape + 1;
        while(nextShape < m_shapes.size()) {
                if(m_shapes[nextShape]) {
                        m_shapes.swap(m_currentShape, nextShape);
                        m_currentShape = nextShape;
                        break;
                }
                ++nextShape;
        }
}

void GroupManager::saveToFile(std::string filename)
{
        std::cout << filename << "\n";
        std::ofstream ofile(filename.c_str(), std::ios_base::trunc);
        if(ofile.fail()) {
                throw "Cannot Save To File!";
        }

        QList<Shape*>::iterator it = m_shapes.begin() + 2;
        while( it != m_shapes.end())
        {
                if((*it) != NULL) {
                        ofile << (*it)->toString();
                }
                it++;
        }
        ofile.close();

}

void GroupManager::restoreFromFile(std::string filename)
{
        std::ifstream ifile(filename.c_str());
        if(ifile.fail()) {
                throw "Cannot read from file";
        }
        int shapeType;
        double pos_x;
        double pos_y;
        double contourWidth;
        double color[4];
        double contourColor[4];
        double size_x, size_y;
	double rotationAngle;



        Shape* shape;

        while((ifile >> shapeType)) {
                if(shapeType) {
                        ifile >> pos_x >> pos_y
                              >> size_x >> size_y
                              >> contourWidth
                              >> color[0] >> color[1] >> color[2] >> color[3]
                              >> contourColor[0] >> contourColor[1] >> contourColor[2] >> contourColor[3]
                              >> rotationAngle;
                        switch(shapeType) {
                            case QUAD:
                                shape = new Quad(pos_x, pos_y);
                                break;
                        }
                        shape->setContourWidth(contourWidth);
                        shape->setFillColor(color[0], color[1], color[2]);
                        shape->setFillColorOpacity(color[3]);
                        shape->setContourColor(QColor(contourColor[0], contourColor[1], contourColor[2]));
                        shape->setContourColorOpacity(contourColor[3]);
                        shape->resize(size_x, size_y);
			shape->rotate(rotationAngle);
                        m_shapes.push_back(shape);
                }
        }

}
