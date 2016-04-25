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

#include <QtGui>

#include "mygcodeeditor.h"

MyGCodeEditor::MyGCodeEditor(QWidget *parent) : QGCodeEditor(parent)
{
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(16);
    setFont(font);

    setPlainText("(* Context menu demo *)\n\nG01 X0 Y0 Z0\n\nM30");

    actionRunFrom = new QAction(this);
    actionRunFrom->setObjectName(QString::fromUtf8("actionRunFrom"));
    actionRunFrom->setText(tr("Run"));
    actionRunFrom->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
}

void MyGCodeEditor::contextMenuEvent(QContextMenuEvent *event)
{
QMenu *menu = createStandardContextMenu();
    menu->addSeparator();
    menu->addAction(actionRunFrom);
    connect(actionRunFrom, SIGNAL(triggered()), this, SLOT(onRunFrom()));
    menu->exec(event->globalPos());
}

void MyGCodeEditor::onRunFrom()
{
    emit runFromSelected(getLineNo());
}
