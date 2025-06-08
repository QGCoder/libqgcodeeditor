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

#include "QGCodeEditor.h"
#include "QGCodeEditorPlugin.h"

#include <QtPlugin>

#include <QtGlobal>
#if QT_VERSION >= QT_VERSION_CHECK(5, 6, 0)
    #include <QtUiPlugin/QDesignerExportWidget>
#else
    #include <QtDesigner/QDesignerExportWidget>
#endif

#ifdef Q_OS_WIN32
#  if QT_VERSION < 0x040100
#    define QDESIGNER_WIDGET_EXPORT QGCODEEDITOR_EXPORT
#  endif
#endif

class QDESIGNER_WIDGET_EXPORT GCodeEditor : public QGCodeEditor
{
public:
  explicit GCodeEditor(QWidget* parent=NULL)
    : QGCodeEditor(parent)
  {
  }
};

QGCodeEditorPlugin::QGCodeEditorPlugin(QObject *parent)
 : QObject(parent)
{
  initialized = false;
}
  
QString QGCodeEditorPlugin::includeFile() const
{
  return QLatin1String("QGCodeEditor.h");
}

bool QGCodeEditorPlugin::isContainer() const
{
  return false;
}
  
bool QGCodeEditorPlugin::isInitialized() const
{
  return initialized;
}
  
QString QGCodeEditorPlugin::codeTemplate() const
{
  return QString("See the QGCodeEditor basic example.");
}
  
QString QGCodeEditorPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QGCodeEditor\" name=\"gcodeEditor\">\n"
		       " <property name=\"geometry\">\n"
		       "  <rect>\n"
		       "   <x>0</x>\n"
		       "   <y>0</y>\n"
		       "   <width>200</width>\n"
		       "   <height>200</height>\n"
		       "  </rect>\n"
		       " </property>\n"
		       "</widget>\n");
}

QString QGCodeEditorPlugin::group() const
{
  return QLatin1String("Display Widgets");
}

QString QGCodeEditorPlugin::name() const
{
  return QLatin1String("QGCodeEditor");
}

QString QGCodeEditorPlugin::toolTip() const
{
  return QString("QGGCodeEditor derived from QPlainTextEdit");
}

QString QGCodeEditorPlugin::whatsThis() const
{
  return QString("QGCodeEditor lets you display and interact with G-Code.");
}

QWidget *QGCodeEditorPlugin::createWidget(QWidget *parent)
{
  return new QGCodeEditor(parent);
}

void QGCodeEditorPlugin::initialize(QDesignerFormEditorInterface *)
{
    initialized = true;
}

QIcon QGCodeEditorPlugin::icon() const
{
  return QIcon();
}

#if QT_VERSION < 0x050000
// First parameter must match the TARGET in .pro
// Second parameter is the class name defined in .h
Q_EXPORT_PLUGIN2(qgcodeeditorplugin, QGCodeEditorPlugin)
#endif
