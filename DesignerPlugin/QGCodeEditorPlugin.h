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

#ifndef QGCODEEDITORPLUGIN_H
#define QGCODEEDITORPLUGIN_H

#include <QtGlobal>

#if QT_VERSION >=  QT_VERSION_CHECK(5, 6, 0)
    #include <QtUiPlugin/QDesignerCustomWidgetInterface>
#else
    #include <QtDesigner/QDesignerCustomWidgetInterface>
#endif

#include <QtCore/qplugin.h>
#include <QtGui/QIcon>

class QGCodeEditorPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetCollectionInterface")
//  Q_PLUGIN_METADATA(IID "QGCodeEditorPlugin" FILE "QGCodeEditorPlugin.json")
#endif
  Q_INTERFACES(QDesignerCustomWidgetInterface)
 public:
  QGCodeEditorPlugin(QObject *parent = NULL);
  bool isContainer() const Q_DECL_OVERRIDE;
  bool isInitialized() const Q_DECL_OVERRIDE;
  QIcon icon() const Q_DECL_OVERRIDE;
  QString codeTemplate() const Q_DECL_OVERRIDE;
  QString domXml() const Q_DECL_OVERRIDE;
  QString group() const Q_DECL_OVERRIDE;
  QString includeFile() const Q_DECL_OVERRIDE;
  QString name() const Q_DECL_OVERRIDE;
  QString toolTip() const Q_DECL_OVERRIDE;
  QString whatsThis() const Q_DECL_OVERRIDE;
  QWidget *createWidget(QWidget *parent) Q_DECL_OVERRIDE;
  void initialize(QDesignerFormEditorInterface *core) Q_DECL_OVERRIDE;

private:
  bool initialized;
};

#endif
