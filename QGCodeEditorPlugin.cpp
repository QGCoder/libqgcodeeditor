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

#include "QGCodeEditorPlugin.h"

#include <QtPlugin>

QGCodeEditorPlugin::QGCodeEditorPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void QGCodeEditorPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool QGCodeEditorPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *QGCodeEditorPlugin::createWidget(QWidget *parent)
{
    return new QGCodeEditor(parent);
}

QString QGCodeEditorPlugin::name() const
{
    return QLatin1String("QGCodeEditor");
}

QString QGCodeEditorPlugin::group() const
{
    return QLatin1String("Custom_Widgets");
}

QIcon QGCodeEditorPlugin::icon() const
{
    return QIcon();
}

QString QGCodeEditorPlugin::toolTip() const
{
    return QLatin1String("");
}

QString QGCodeEditorPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool QGCodeEditorPlugin::isContainer() const
{
    return false;
}

QString QGCodeEditorPlugin::domXml() const
{
    return QLatin1String("<widget class=\"QGCodeEditor\" name=\"QGCodeEditor\">\n</widget>\n");
}

QString QGCodeEditorPlugin::includeFile() const
{
    return QLatin1String("QGCodeEditorPlugin.h");
}

