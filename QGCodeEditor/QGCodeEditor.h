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
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
********************************************************************/

#ifndef _QGCODE_EDITOR_
#define _QGCODE_EDITOR_

#include <QObject>
#include <QPlainTextEdit>
#include <QAction>
#include <QMenu>
#include <QDebug>
#include <QTextBlock>

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;

class LineNumberArea;

// editor can only judge size by lines, has no concept of file size
    // render initial 200 lines
#define CHUNK_SIZE 200
    // add in 100 lines dynamically
#define ADD_SIZE 100

class Q_DECL_EXPORT QGCodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    QGCodeEditor(QWidget *parent = 0);
    
    virtual ~QGCodeEditor();

    QString getCurrentText();
    QString formatLine(QString);

    int firstBlockNum() const{return ( (int) (QPlainTextEdit::firstVisibleBlock()).blockNumber() );  }

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int  lineNumberAreaWidth();
    int  getLineNo();
    int  getLineCount();
    void cursorUp();
    void cursorDown();
    void highlightLine(int);

    void appendNewPlainText(const QString &);
    void clear();
    bool isModified();

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    virtual void updateLineNumberAreaWidth(int newBlockCount);
    virtual void highlightCurrentLine();
    virtual void updateLineNumberArea(const QRect &, int);
    virtual void loadNextChunk();

private:
    QWidget *lineNumberArea;
    bool bMoreBig, bBigFile;
    int linesIn;
    QStringList *excess;
    QStringList *contents;

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

#endif
