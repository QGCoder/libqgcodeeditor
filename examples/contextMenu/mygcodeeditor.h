/********************************************************************
* Copyright (C) 2016 Jakob Flierl <jakob.flierl AT gmail.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
********************************************************************/

#ifndef _MY_GCODE_EDITOR_
#define _MY_GCODE_EDITOR_

#include <QGCodeEditor/QGCodeEditor.h>

class MyGCodeEditor : public QGCodeEditor
{
    Q_OBJECT

public:
    MyGCodeEditor(QWidget *parent = 0);

Q_SIGNALS:
    void runFromSelected(int line);

protected:
    void contextMenuEvent(QContextMenuEvent *event);

public slots:
    virtual void onRunFrom();

private:
    QAction *actionRunFrom;
};

#endif
