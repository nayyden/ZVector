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

#include "qdrawmainwindow.h"
#include "ui_qdrawmainwindow.h"
#include "qtcolortriangle.h"

QDrawMainWindow::QDrawMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::QDrawMainWindow)
{
	ui->setupUi(this);

	m_debug = new GLDebugBufferWidget(this);

	ui->mdiArea->addSubWindow(m_debug);

}

QDrawMainWindow::~QDrawMainWindow()
{
	QList<QMdiSubWindow*> wins = ui->mdiArea->subWindowList();
	QList<QMdiSubWindow*>::iterator it = wins.begin();
	while(it != wins.end())
	{
		delete *it;
		it++;
	}
	delete ui;
}

void QDrawMainWindow::redrawSelectBuffer()
{
	GLCanvas* activeCanvas = (GLCanvas*)ui->mdiArea->activeSubWindow()->widget();
	activeCanvas->redrawSelectionBufer();
}

void QDrawMainWindow::on_actionSelect_triggered()
{
	emit changeTool(ToolFactory::getSingletonPtr()->getSelectTool());
}

void QDrawMainWindow::on_actionCreate_triggered()
{
	emit changeTool(ToolFactory::getSingletonPtr()->getCreateQuadTool());
}

void QDrawMainWindow::on_actionMove_triggered()
{
	emit changeTool(ToolFactory::getSingletonPtr()->getTranslateTool());
}

void QDrawMainWindow::on_actionNew_triggered()
{
	GLCanvas* canvas = new GLCanvas(this);
	connect(this, SIGNAL(changeTool(Tool*)), canvas, SLOT(changeTool(Tool*)));
	connect(canvas, SIGNAL(sendFrameBuffer(QImage)), m_debug, SLOT(drawBuffer(QImage)));

	// Color <-> Shape connection
	connect(ui->colorTriangle, SIGNAL(colorChanged(QColor)), canvas, SLOT(setCurrentGroupColor(QColor)));
	connect(ToolFactory::getSingletonPtr()->getSelectTool(), SIGNAL(refreshColorPane(QColor)), ui->colorTriangle, SLOT(setColor(QColor)));

	ui->mdiArea->addSubWindow(canvas);

	canvas->setWindowTitle("New Drawing*");
	canvas->show();
}


void QDrawMainWindow::on_actionDraw_Ellipse_triggered()
{
	emit(changeTool(ToolFactory::getSingletonPtr()->getCreateEllipseTool()));
}

void QDrawMainWindow::on_actionDraw_Triangle_triggered()
{
	emit(changeTool(ToolFactory::getSingletonPtr()->getTriangleTool()));
}
