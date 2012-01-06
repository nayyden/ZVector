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
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>

QDrawMainWindow::QDrawMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::QDrawMainWindow)
{
	ui->setupUi(this);

        ui->angleSpinbox->setRange(-360, 360);

        connect(ToolFactory::getSingletonPtr()->getSelectTool(), SIGNAL(shapeChanged(Shape*)),
                this, SLOT(updateWidgetsForSelectedShape(Shape*)));
        connect(ToolFactory::getSingletonPtr()->getTranslateTool(), SIGNAL(shapeChanged(Shape*)),
                this, SLOT(updateWidgetsForSelectedShape(Shape*)));
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

void QDrawMainWindow::on_actionGroup_triggered()
{
        GLCanvas* activeCanvas = (GLCanvas*)ui->mdiArea->activeSubWindow()->widget();
        activeCanvas->groupSelectedShapes();
}

void QDrawMainWindow::on_actionUngroup_triggered()
{

	if(QMdiSubWindow* wnd = ui->mdiArea->activeSubWindow())
        {
                GLCanvas* activeCanvas = (GLCanvas*)wnd->widget();
		activeCanvas->collapseSelectedGroup();               
        }
    
}

void QDrawMainWindow::on_colorTriangle_colorChanged(const QColor &color)
{
        if(QMdiSubWindow* wnd = ui->mdiArea->activeSubWindow())
        {
                GLCanvas* activeCanvas = (GLCanvas*)wnd->widget();
                Shape* shape = activeCanvas->getCurrentShape();
                if(ui->fill->isChecked())
                {
                        shape->setFillColor(color);
                }
                else if(ui->outline->isChecked())
                {
                        shape->setContourColor(color);
                }
                activeCanvas->flush();
        }
}

void QDrawMainWindow::on_mdiArea_subWindowActivated(QMdiSubWindow *)
{
        //GLCanvas* activeCanvas = (GLCanvas*)canvas->widget();
        // TODO: send cursor position somehow
}

void QDrawMainWindow::on_opacity_valueChanged(int value)
{
        ui->opacity_value->setText(QString::number(value)+QString('%'));
        if(QMdiSubWindow* wnd = ui->mdiArea->activeSubWindow())
        {
                GLCanvas* activeCanvas = (GLCanvas*)wnd->widget();
                Shape* shape = activeCanvas->getCurrentShape();
                if(ui->fill->isChecked())
                {
                        shape->setFillColorOpacity((double)value/100);
                }
                else if(ui->outline->isChecked())
                {
                        shape->setContourColorOpacity((double)value/100);
                }
                activeCanvas->flush();
        }
}

void QDrawMainWindow::on_outline_width_valueChanged(int value)
{
        if(QMdiSubWindow* wnd = ui->mdiArea->activeSubWindow())
        {
                GLCanvas* activeCanvas = (GLCanvas*)wnd->widget();
                activeCanvas->getCurrentShape()->setContourWidth(value);
                activeCanvas->flush();
        }
}

void QDrawMainWindow::updateWidgetsForSelectedShape(Shape* shape)
{
        if(ui->fill->isChecked())
        {
                ui->colorTriangle->setColor(shape->getFillColor());
                ui->opacity->setValue(shape->getFillOpacity()*100);
        }
        else if(ui->outline->isChecked())
        {
                ui->colorTriangle->setColor(shape->getContourColor());
                ui->opacity->setValue(shape->getContourOpacity()*100);
        }
        ui->angleSpinbox->setValue(shape->getRotationAngle());
        ui->outline_width->setValue(shape->getContourWidth());

        if(AutoShape* autoShape = dynamic_cast<AutoShape*>(shape))
        {
                ui->autoShapeDetails->setEnabled(true);
                ui->autoShapeDetails->setValue(autoShape->getNumDetails());
        }
        else
        {
                ui->autoShapeDetails->setEnabled(false);
        }
}


void QDrawMainWindow::on_actionReset_Zoom_triggered()
{
        if(QMdiSubWindow* wnd = ui->mdiArea->activeSubWindow())
        {
                GLCanvas* activeCanvas = (GLCanvas*)wnd->widget();
                activeCanvas->setZoomFactor(1.f);
        }
}

void QDrawMainWindow::on_autoShapeDetails_valueChanged(int details)
{
        if(QMdiSubWindow* wnd = ui->mdiArea->activeSubWindow())
        {
                GLCanvas* activeCanvas = (GLCanvas*)wnd->widget();
                if( AutoShape* shape =  dynamic_cast<AutoShape*>(activeCanvas->getCurrentShape()))
                {
                        shape->setNumDetails(details);
                        activeCanvas->flush();
                }
        }
}

void QDrawMainWindow::on_angleSpinbox_valueChanged(int angle)
{
        rotateCurrentShapeBy(angle);
}

void QDrawMainWindow::on_rotatePlus90_clicked()
{
        rotateCurrentShapeBy(90);
        ui->angleSpinbox->setValue(90);
}

void QDrawMainWindow::on_rotateMinus90_clicked()
{
        rotateCurrentShapeBy(-90);
        ui->angleSpinbox->setValue(-90);
}

void QDrawMainWindow::rotateCurrentShapeBy(int angle)
{
        if(QMdiSubWindow* wnd = ui->mdiArea->activeSubWindow())
        {
                GLCanvas* activeCanvas = (GLCanvas*)wnd->widget();
                if(Shape* shape = activeCanvas->getCurrentShape())
                {
                        shape->rotate(angle);
                        activeCanvas->flush();
                }
        }

}

void QDrawMainWindow::keyPressEvent(QKeyEvent* )
{
}

void QDrawMainWindow::on_pushShapeBack_clicked()
{
        if(QMdiSubWindow* wnd = ui->mdiArea->activeSubWindow())
        {
                GLCanvas* activeCanvas = (GLCanvas*)wnd->widget();
                activeCanvas->pushCurrentShapeBack();
                activeCanvas->flush();

        }
}

void QDrawMainWindow::on_popShapeFront_clicked()
{
        if(QMdiSubWindow* wnd = ui->mdiArea->activeSubWindow())
        {
                GLCanvas* activeCanvas = (GLCanvas*)wnd->widget();
                activeCanvas->popCurrentShapeFront();
                activeCanvas->flush();

        }

}

void QDrawMainWindow::on_doTranslate_clicked()
{
        if(QMdiSubWindow* wnd = ui->mdiArea->activeSubWindow())
        {
                GLCanvas* activeCanvas = (GLCanvas*)wnd->widget();
                if(Shape* shape = activeCanvas->getCurrentShape())
                {
                        shape->translate(ui->xUnitSpinBox->value(), ui->yUnitSpinBox->value());
                        ui->xUnitSpinBox->setValue(0);
                        ui->yUnitSpinBox->setValue(0);
                        activeCanvas->flush();
                }
        }

}

void QDrawMainWindow::on_actionSave_as_triggered()
{
      
       if(QMdiSubWindow* wnd = ui->mdiArea->activeSubWindow())
       {
              QString fullPathToFile =  QFileDialog::getSaveFileName(this, tr("Save as..."), "./",  tr("ZVector drawing (*.zdrw)"));
              if(fullPathToFile.isEmpty()) {
                      return;
              }
	      
	      QStringList splitted = fullPathToFile.split("/");
	      QString filename = splitted.at(splitted.size() - 1);	      
              GLCanvas* activeCanvas = (GLCanvas*)wnd->widget();
              try {
                       activeCanvas->saveSceneToFile(fullPathToFile.toStdString());
		       activeCanvas->setWindowTitle(filename);
              } catch (const char* exception) {
                      QMessageBox::warning(this, tr("ZVector"), tr("Cannot save file!"));
              }
             
       }

}

void QDrawMainWindow::on_actionOpen_triggered()
{
        if(QMdiSubWindow* wnd = ui->mdiArea->activeSubWindow())
        {
                QString fullPathToFile = QFileDialog::getOpenFileName(this, tr("Open..."), "./", tr("Zvector drawing (*.zdrw)"));
                if(fullPathToFile.isEmpty()) {
                        return;
                }
                
        
                GLCanvas* activeCanvas = (GLCanvas*)wnd->widget();
		QStringList splitted = fullPathToFile.split("/");
		QString filename = splitted.at(splitted.size() - 1);
                try {
                        activeCanvas->restoreSceneFromFile(fullPathToFile.toStdString());
			activeCanvas->setWindowTitle(filename);
                } catch (const char* exception) {
                         QMessageBox::warning(this, tr("ZVector"), tr("Cannot open file!"));
                }
        }
}


