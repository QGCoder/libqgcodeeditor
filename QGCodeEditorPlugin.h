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

#ifndef _QGCODE_EDITOR_PLUGIN_
#define _QGCODE_EDITOR_PLUGIN_

#include "qt_includes.h"


///////////////////////////////////////////////////////////////////////////////////////

#include <QPlainTextEdit>
#include <QObject>
#include <QtDebug>
#include <QAction>
#include <QMenu>

#include "comment_highlighter.h"

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;

class LineNumberArea;


class QGCodeEditor : public QPlainTextEdit
{
	Q_OBJECT
	
public:
	QGCodeEditor(QWidget *parent = 0);
	
	QString getCurrentText();
	QString formatLine(QString);
	
	void lineNumberAreaPaintEvent(QPaintEvent *event);
	int lineNumberAreaWidth();
	int getLineNo();
	int getLineCount();
	void cursorUp();
	void cursorDown();
	void highlightLine(int);
	QAction *actionRunFrom;
	
	bool isModified();
	void appendNewPlainText(const QString &);
	void clear();
	QStringList contents;
	
Q_SIGNALS:
	void runFromSelected(int line);
	
protected:
	void resizeEvent(QResizeEvent *event);
	void contextMenuEvent(QContextMenuEvent *event);
	
	
private slots:
	virtual void updateLineNumberAreaWidth(int newBlockCount);
	virtual void highlightCurrentLine();
	virtual void updateLineNumberArea(const QRect &, int);
	virtual void onRunFrom();
	
private:
	QWidget *lineNumberArea;
	CommentHighlighter *hiLite;
};


class LineNumberArea : public QWidget
{
public:
	LineNumberArea(QGCodeEditor *editor) : QWidget(editor) {
		codeEditor = editor;
	}
	
	QSize sizeHint() const {
		return QSize(codeEditor->lineNumberAreaWidth(), 0);
	}
	
protected:
	void paintEvent(QPaintEvent *event) {
		codeEditor->lineNumberAreaPaintEvent(event);
	}
	
private:
	QGCodeEditor *codeEditor;
};


///////////////////////////////////////////////////////////////////////////////////////

class QDESIGNER_WIDGET_EXPORT QGCodeEditorPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    QGCodeEditorPlugin(QObject *parent = 0);

    bool isContainer() const;
    bool isInitialized() const;
    QIcon icon() const;
    QString domXml() const;
    QString group() const;
    QString includeFile() const;
    QString name() const;
    QString toolTip() const;
    QString whatsThis() const;
    QWidget *createWidget(QWidget *parent);
    void initialize(QDesignerFormEditorInterface *core);

private:
    bool m_initialized;

};

#endif
/////////////////////////////////////////////////////////////////////////////////////////