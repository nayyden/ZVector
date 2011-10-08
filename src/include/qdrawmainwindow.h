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

#ifndef QDRAWMAINWINDOW_H
#define QDRAWMAINWINDOW_H

#include <QMainWindow>
#include "glcanvas.h"
namespace Ui {
    class QDrawMainWindow;
}

class QDrawMainWindow : public QMainWindow
{
    Q_OBJECT
private:


public:
    explicit QDrawMainWindow(QWidget *parent = 0);
    ~QDrawMainWindow();

private:
    Ui::QDrawMainWindow *ui;
};

#endif // QDRAWMAINWINDOW_H
