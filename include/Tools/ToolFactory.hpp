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
#include "CreateQuadTool.hpp"
#include "TranslateTool.hpp"
#include "CreateEllipseTool.hpp"
#include "CreateTriangleTool.hpp"

class ToolFactory
{
public:
	static ToolFactory* getSingletonPtr();

	// Methods to obtain tool
	Tool* getSelectTool();
	Tool* getResizeTool();
	Tool* getCreateQuadTool();
	Tool* getTranslateTool();
	Tool* getCreateEllipseTool();
	Tool* getTriangleTool();

private:
	ToolFactory();
	virtual ~ToolFactory();

	static ToolFactory* m_pInstance;

	SelectTool* m_pSelect;
	ResizeTool* m_pResize;
	CreateQuadTool* m_pCreateQuad;
	CreateEllipseTool* m_pCreateEllipse;
	TranslateTool* m_pTranslate;
	CreateTriangleTool* m_pCreateTriangle;
};

#endif // TOOLFACTORY_HPP
