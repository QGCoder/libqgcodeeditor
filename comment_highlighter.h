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

#ifndef COMMENT_HIGHLIGHTER_H
#define COMMENT_HIGHLIGHTER_H

#include <QSyntaxHighlighter>

#include <QHash>
#include <QTextCharFormat>


class CommentHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    CommentHighlighter(QTextDocument *parent = 0);
protected:
    void highlightBlock(const QString &text);

private:
    struct HighlightingRule
       {
       QRegExp pattern;
       QTextCharFormat format;
       };
    QVector<HighlightingRule> highlightingRules;

    QTextCharFormat semicolonCommentFormat;
    QTextCharFormat braceCommentFormat;
    QTextCharFormat M_WordFormat;
    QTextCharFormat G_WordFormat;
    QTextCharFormat F_WordFormat;
    QTextCharFormat S_WordFormat;
    QTextCharFormat PQ_WordFormat;
    QTextCharFormat XYZ_WordFormat;
    QTextCharFormat IJKR_WordFormat;
    QTextCharFormat Param_WordFormat;            
};

#endif
