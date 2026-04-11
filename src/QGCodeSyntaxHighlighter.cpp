/**
 * @file QGCodeSyntaxHighlighter.cpp
 * @brief Implementation of QGCodeSyntaxHighlighter for G-code syntax highlighting
 */

#include "QGCodeSyntaxHighlighter.h"

#include <QSyntaxHighlighter>

#include "QGCodeEditor.h"

/**
 * @class QGCodeSyntaxHighlighter
 * @brief Syntax highlighter for G-code (CNC machine control language)
 *
 * Highlights different G-code commands with distinct colors:
 * - M/T words: Red
 * - G words: Green
 * - F words: Yellow
 * - S words: Magenta
 * - P/Q words: Green
 * - X/Y/Z/A/B/C/U/V/W coordinates: Yellow
 * - I/J/K/R arcs: Dark Gray
 * - Parameters (#): Cyan
 * - Comments (; and ()): White/Magenta
 */

/**
 * @brief Constructor
 * @param parent Parent QTextDocument object
 *
 * Initializes all highlighting rules for G-code syntax elements.
 */
QGCodeSyntaxHighlighter::QGCodeSyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
HighlightingRule rule;

    //  The escape sequence \s should denote a space and it says so in the docs
    //  but if you use it you get a 'unrecognised escape char' warning so use \x20 instead

    M_WordFormat.setForeground(Qt::red);
    M_WordFormat.setFontWeight(QFont::Bold);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    rule.pattern = QRegularExpression("[mMtT][^\\x20]*");
#else
    rule.pattern = QRegExp("[mMtT][^\\x20]*");
#endif
    rule.format = M_WordFormat;
    highlightingRules.append(rule);

    G_WordFormat.setForeground(Qt::green);
    G_WordFormat.setFontWeight(QFont::Bold);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    rule.pattern = QRegularExpression("[gG][^\\x20]*");
#else
    rule.pattern = QRegExp("[gG][^\\x20]*");
#endif
    rule.format = G_WordFormat;
    highlightingRules.append(rule);

    F_WordFormat.setForeground(Qt::yellow);
    F_WordFormat.setFontWeight(QFont::Bold);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    rule.pattern = QRegularExpression("[fF][^\\x20 ]*");
#else
    rule.pattern = QRegExp("[fF][^\\x20 ]*");
#endif
    rule.format = F_WordFormat;
    highlightingRules.append(rule);

    S_WordFormat.setForeground(Qt::magenta);
    S_WordFormat.setFontWeight(QFont::Bold);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    rule.pattern = QRegularExpression("[sS][^\\x20 ]*");
#else
    rule.pattern = QRegExp("[sS][^\\x20 ]*");
#endif
    rule.format = S_WordFormat;
    highlightingRules.append(rule);

    PQ_WordFormat.setForeground(Qt::green);
    PQ_WordFormat.setFontWeight(QFont::Bold);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    rule.pattern = QRegularExpression("[pPqQ][^\\x20 ]*");
#else
    rule.pattern = QRegExp("[pPqQ][^\\x20 ]*");
#endif
    rule.format = PQ_WordFormat;
    highlightingRules.append(rule);

    XYZ_WordFormat.setForeground(Qt::yellow);
    XYZ_WordFormat.setFontWeight(QFont::Bold);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    rule.pattern = QRegularExpression("[xXyYzZaAbBcCuUvVwW][^\\x20 ]*");
#else
    rule.pattern = QRegExp("[xXyYzZaAbBcCuUvVwW][^\\x20 ]*");
#endif
    rule.format = XYZ_WordFormat;
    highlightingRules.append(rule);

    IJKR_WordFormat.setForeground(Qt::darkGray);
    IJKR_WordFormat.setFontWeight(QFont::Bold);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    rule.pattern = QRegularExpression("[iIjJkKrR][^\\x20 ]*");
#else
    rule.pattern = QRegExp("[iIjJkKrR][^\\x20 ]*");
#endif
    rule.format = IJKR_WordFormat;
    highlightingRules.append(rule);

    Param_WordFormat.setForeground(Qt::cyan);
    Param_WordFormat.setFontWeight(QFont::Bold);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    rule.pattern = QRegularExpression("#[^\\x20 ]*");
#else
    rule.pattern = QRegExp("#[^\\x20 ]*");
#endif
    rule.format = Param_WordFormat;
    highlightingRules.append(rule);

    // do comments last then won't get colouring of text containing M G F S T etc
    semicolonCommentFormat.setForeground(Qt::white);
    semicolonCommentFormat.setFontWeight(QFont::Bold);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    rule.pattern = QRegularExpression(";[^\\n]*");
#else
    rule.pattern = QRegExp(";[^\\n]*");
#endif
    rule.format = semicolonCommentFormat;
    highlightingRules.append(rule);

    braceCommentFormat.setForeground(Qt::magenta);
    braceCommentFormat.setFontWeight(QFont::Bold);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    rule.pattern = QRegularExpression("\\([^\\n]*");
#else
    rule.pattern = QRegExp("\\([^\\n]*");
#endif
    rule.format = braceCommentFormat;
    highlightingRules.append(rule);
}

/**
 * @brief Highlights a single block of text
 * @param text The text block to highlight
 *
 * Applies all matching highlighting rules to the given text block,
 * coloring G-code commands and comments appropriately.
 */
void QGCodeSyntaxHighlighter::highlightBlock(const QString &text)
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    for (const HighlightingRule &rule : highlightingRules)
        {
        QRegularExpressionMatchIterator it = rule.pattern.globalMatch(text);
        while (it.hasNext())
            {
            QRegularExpressionMatch match = it.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
            }
        }
#else
    foreach (const HighlightingRule &rule, highlightingRules)
        {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0)
            {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
            }
        }
#endif
    setCurrentBlockState(0);
}