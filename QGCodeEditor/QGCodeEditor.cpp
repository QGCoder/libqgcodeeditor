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

#include <QtGui>

#include "QGCodeEditor.h"

#include "QGCodeSyntaxHighlighter.h"

/////////////////////////////////////////////////////////////////////////////
// this class is used in Designer directly as a  widget
//
// New functions:
// * cursorUp()
// * cursorDown()
// * getLineNo()
// * highlightLine()
// * isModified()
// Overloaded:
// * appendNewPlainText(const QString &text)
// * clear()
// SubClassed
// * firstBlockNum() // first block in the viewport

/////////////////////////////////////////////////////////////////////////////

QGCodeEditor::QGCodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    updateLineNumberAreaWidth(0);

    bMoreBig = bBigFile = false;
    linesIn = 0;

    /*
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(11);

    setFont(font);*/

    new QGCodeSyntaxHighlighter(document());

    highlightCurrentLine();

    excess = new QStringList();
    contents = new QStringList();

}

QGCodeEditor::~QGCodeEditor()
{
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// formats first and adds to QStringList before appending 
// for later comparison using list to test if text changed
//
// Need to have editor deal with large inputs, by rendering first
// chunk then caching rest to prevent GUI lock ups
//
// This method has taken a 30 sec load time of a 10000 line file into just
// the editor, to a 5 sec load into both editor and GL viewer
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void QGCodeEditor::appendNewPlainText(const QString &text)
{
QString str;
QFile file("/tmp/qgc_cache");

    if(!bBigFile)   // not reached 200 lines yet
        {
        // format the text to space entries if necessary
        str = formatLine(text);
        contents->append(str);
        QPlainTextEdit::appendPlainText(str);
        if(++linesIn > CHUNK_SIZE) // when it gets to 201
            bBigFile = true;
        }
    else
        {
        str = formatLine(text);
        excess->append(str);
        if(!bMoreBig)
            bMoreBig = true;  // file is 200 lines AND it is cached
        }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// overloaded to clear the QStringList first

void QGCodeEditor::clear()
{
    excess->clear();
    contents->clear();
    QPlainTextEdit::clear();
    bBigFile = bMoreBig = false;
    linesIn = 0;
}

QString QGCodeEditor::formatLine(QString text)
{
QString str, str2;
QStringList list;
    // get rid of extra spaces, convert to UC and make 2 copies
    str = text;
    str = str.simplified();
    str2 = str = str.toUpper();

    // deal with comments in str2
    // if starts with ( or ; bypass altogether)
    if(str2.startsWith('(') || str2.startsWith(';') )
        return str2;

    if(str2.contains('(') )
        {
        list = str2.split("(");
        str = list[0];
        str2 = " (" + list[1];
        }
    else if(str2.contains(';') )
        {
        list = str2.split(";", QString::SkipEmptyParts); // skip because could have 2 or more ;
        str = list[0];
        str2 = " ;" + list[1];
        }
    else
        str2 = "";
    // now process str, which either contains whole string
    // or one before comments

    // get rid of line numbers
    str.remove(QRegExp("N([0-9]*)"));
    // space G Code elements for readability
    str.replace(QRegExp("G([0-9]*)"), " G\\1");
    str.replace(QRegExp("M([0-9]*)"), " M\\1");
    str.replace(QRegExp("F([0-9]*)"), " F\\1");
    str.replace(QRegExp("S([0-9]*)"), " S\\1");
    str.replace(QRegExp("P([0-9]*)"), " P\\1");
    str.replace(QRegExp("Q([0-9]*)"), " Q\\1");
    str.replace(QRegExp("X([0-9]*)"), " X\\1");
    str.replace(QRegExp("Y([0-9]*)"), " Y\\1");
    str.replace(QRegExp("Z([0-9]*)"), " Z\\1");
    str.replace(QRegExp("I([0-9]*)"), " I\\1");
    str.replace(QRegExp("J([0-9]*)"), " J\\1");
    str.replace(QRegExp("K([0-9]*)"), " K\\1");
    str.replace(QRegExp("R([0-9]*)"), " R\\1");
    // get rid of any double spacing and leading spaces
    str.replace(QRegExp("  "), " ");
    str = str.simplified();
    // push to 2nd line if stupidly been put on same line
    if(str2.length())
        str = str + "\n" + str2;

    return str;
}

/////////////////////////////////////////////////////////////////////////////////////

// big problem with the base editor was that it registers that document changed and that
// modification changed (usually by using Ctrl Z or Ctrl Shift Z)
// but you still could not tell if the document is now different overall or not
// By saving a copy of what was loaded and then comparing it to what is present, it
// reports accurately on any change.

bool QGCodeEditor::isModified()
{
    QString txt = toPlainText();
    QStringList list = txt.split( "\n");
    
    if( contents->size() != list.size() )
        return true;
    
    for(int x = 0; x < contents->size(); x++)
        {
        if( contents->at(x) != list[x] )
            return true;
        }
    return false;
}


QString QGCodeEditor::getCurrentText()
{
QTextDocument *doc = document();

    QTextBlock block = doc->findBlock( textCursor().position());
    return(block.text().trimmed().toLatin1());
}

void QGCodeEditor::cursorUp()
{
    moveCursor(QTextCursor::PreviousBlock);
}

void QGCodeEditor::cursorDown()
{
    moveCursor(QTextCursor::NextBlock);
}

int QGCodeEditor::getLineNo()
{
int numBlocks = blockCount();
QTextDocument *doc = document();

    QTextBlock blk = doc->findBlock( textCursor().position() );
    QTextBlock blk2 = doc->begin();

    for(int x = 1; x <= numBlocks; x++)
        {
        if(blk == blk2)
            return x;
        blk2 = blk2.next();
        }
    return 0;
}

void QGCodeEditor::highlightLine(int line)
{
int num = 0;

    // when file loaded, highlights first blank line at end with EOF,
    // so never matched and returns 0 unless go up 1 first

    if( blockCount()) 
        {
        if(line > 0 && line <= blockCount()) 
            {
            cursorUp();
            num = getLineNo();
            if(num > line) 
                {
                do
                    {
                    cursorUp();
                    num--;
                    }while(num > line);
                }
            else
                {
                while(num < line)
                    {
                    cursorDown();
                    num++;
                    }
                }
            }
        else
            qDebug() << "Invalid line number passed";
        }
    else
        qDebug() << "No blocks found";
}

int QGCodeEditor::getLineCount() 
{
    return blockCount() - 1;
}

///////////////////////////////////////////////////////////////////////////////////

int QGCodeEditor::lineNumberAreaWidth()
{
int digits = 1;
int max = qMax(1, blockCount());

    while (max >= 10) 
        {
        max /= 10;
        ++digits;
        }

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void QGCodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void QGCodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void QGCodeEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void QGCodeEditor::highlightCurrentLine()
{
QList<QTextEdit::ExtraSelection> extraSelections;

QTextEdit::ExtraSelection selection;

QColor lineColor = QColor(Qt::yellow).lighter(160);

    selection.format.setBackground(lineColor);
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    selection.cursor = textCursor();
    selection.cursor.clearSelection();
    extraSelections.append(selection);

    setExtraSelections(extraSelections);
    
    // This function is triggered by the append actions to the editor
    // once 200 lines have been appended, begin background 
    // load of remainder
    if(bMoreBig)
        loadNextChunk();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void QGCodeEditor::loadNextChunk()
{
int x, y;
QString str;

    if(bMoreBig)
        {
        y = excess->size();
    if(y > ADD_SIZE) {
        y = ADD_SIZE;
    }

        for ( x = 0; x < y  ; x++)
            {
            str = excess->at(x);
            str = formatLine(str);
            contents->append(str);
            QPlainTextEdit::appendPlainText(str);
            }
        // It is quite possible lines could still be being added to the end of the list
        // whilst reading and removing from front.
        // This appears safest method of removal, making no size assumptions
        for( y = 0; y < x && !excess->isEmpty(); y++)
            excess->removeFirst();

        if(excess->isEmpty()) {
            bMoreBig = false;
	}
        }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void QGCodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
QPainter painter(lineNumberArea);

    //painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) 
        {
        if (block.isVisible() && bottom >= event->rect().top()) 
            {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::yellow);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
            }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
        }
}
