/********************************************************************
* Copyright (C) 2010 - 2016 ArcEye <arceye AT mgware DOT co DOT uk>
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

#include "QGCodeEditorWidget.h"

#include "QGCodeEditorPlugin.h"

QGCodeEditorWidget::QGCodeEditorWidget(QObject *parent)
    : QObject(parent)
{
    widget.append(new QGCodeEditorPlugin(this));
}

QList<QDesignerCustomWidgetInterface*> QGCodeEditorWidget::customWidgets() const
{
    return widget;
}

