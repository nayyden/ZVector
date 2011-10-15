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

#ifndef TOOLFACTORY_HPP
#define TOOLFACTORY_HPP

// include all tools
#include "Tool.hpp"
#include "SelectTool.hpp"
#include "ResizeTool.hpp"
#include "CreateTool.hpp"


class ToolFactory{
public:
   static ToolFactory* getSingletonPtr()
   {
      if (!m_pInstance)
         m_pInstance = new ToolFactory;

      return m_pInstance;
   }
   // Methods to obtain tool
   inline Tool* getSelectTool()
   {
       return m_pSelect;
   }

   inline Tool* getResizeTool()
   {
       if( !m_pResize )
           m_pResize = new ResizeTool();
       return m_pResize;
   }

   inline Tool* getCreateTool()
   {
       if( !m_pCreate )
           m_pCreate = new CreateTool();
       return m_pCreate;
   }

private:
   ToolFactory(){
       m_pSelect = new SelectTool();
       m_pResize = NULL;
       m_pCreate = NULL;
   }

   virtual ~ToolFactory(){
       if(m_pSelect)
           delete m_pSelect;
       if(m_pResize)
           delete m_pResize;
       if(m_pCreate)
           delete m_pCreate;
   }

   static ToolFactory* m_pInstance;

   SelectTool* m_pSelect;
   ResizeTool* m_pResize;
   CreateTool* m_pCreate;
};

#endif // TOOLFACTORY_HPP
