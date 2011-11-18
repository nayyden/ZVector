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

#include "ToolFactory.hpp"

ToolFactory* ToolFactory::getSingletonPtr()
{
	if (!m_pInstance)
		m_pInstance = new ToolFactory;

	return m_pInstance;
}
// Methods to obtain tool
Tool* ToolFactory::getSelectTool()
{
	return m_pSelect;
}

Tool* ToolFactory::getResizeTool()
{
	if( !m_pResize )
		m_pResize = new ResizeTool();
	return m_pResize;
}

Tool* ToolFactory::getCreateQuadTool()
{
	if( !m_pCreateQuad )
		m_pCreateQuad = new CreateQuadTool();
	return m_pCreateQuad;
}

Tool* ToolFactory::getTranslateTool()
{
	if( !m_pTranslate )
		m_pTranslate = new TranslateTool();
	return m_pTranslate;
}

Tool* ToolFactory::getCreateEllipseTool()
{
	if(!m_pCreateEllipse)
		m_pCreateEllipse = new CreateEllipseTool();
	return m_pCreateEllipse;
}

Tool* ToolFactory::getTriangleTool()
{
	if(!m_pCreateTriangle)
		m_pCreateTriangle = new CreateTriangleTool();
	return m_pCreateTriangle;
}

ToolFactory::ToolFactory()
{
	m_pSelect = new SelectTool();
	m_pResize = NULL;
	m_pCreateEllipse = NULL;
	m_pTranslate = NULL;
	m_pCreateQuad = NULL;
	m_pCreateTriangle = NULL;
}

ToolFactory::~ToolFactory()
{
	if(m_pSelect)
		delete m_pSelect;
	if(m_pResize)
		delete m_pResize;
	if(m_pTranslate)
		delete m_pTranslate;
	if(m_pCreateQuad)
		delete m_pCreateQuad;
	if(m_pCreateTriangle)
		delete m_pCreateTriangle;
}
