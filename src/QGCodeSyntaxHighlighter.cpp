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
 * - Comments (; to end of line, and (...)): Magenta
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

    // Comments are not matched by regexp rules, they are located by
    // findComments() in highlightBlock() so that a ';' really does comment out
    // the rest of the line and a '(' inside such a comment stays comment text.
    semicolonCommentFormat.setForeground(Qt::magenta);
    semicolonCommentFormat.setFontWeight(QFont::Bold);

    braceCommentFormat.setForeground(Qt::magenta);
    braceCommentFormat.setFontWeight(QFont::Bold);
}

namespace
{

struct CommentSpan
    {
    // qsizetype, not int: that is what QString indexes and measures itself in
    // under Qt 6, and narrowing it here warned on every build
    qsizetype start;
    qsizetype length;
    bool semicolon;
    };

/**
 * @brief Locates the comment regions of a single line of g-code
 * @param text The line to scan
 * @return The comments found, in the order they appear
 *
 * A ';' comments out everything up to the end of the line, a '(' opens a
 * comment which is closed by the next ')' (or by the end of the line if the
 * ')' is missing).  A ';' inside a '(...)' comment is ordinary comment text,
 * as is a '(' following a ';'.
 */
QVector<CommentSpan> findComments(const QString &text)
{
QVector<CommentSpan> comments;

    for (qsizetype i = 0; i < text.length(); ++i)
        {
        if (text.at(i) == QLatin1Char(';'))
            {
            comments.append({i, text.length() - i, true});
            break;              // rest of the line is comment
            }
        if (text.at(i) == QLatin1Char('('))
            {
            const qsizetype close = text.indexOf(QLatin1Char(')'), i + 1);
            const qsizetype last = (close < 0) ? text.length() - 1 : close;
            comments.append({i, last - i + 1, false});
            i = last;           // resume scanning after the closing brace
            }
        }
    return comments;
}

}  // namespace

/**
 * @brief Highlights a single block of text
 * @param text The text block to highlight
 *
 * The comments are located first and blanked out of the text the word rules
 * are matched against, so that g-code letters appearing inside a comment are
 * not coloured as commands.  The comments themselves are coloured afterwards.
 */
void QGCodeSyntaxHighlighter::highlightBlock(const QString &text)
{
const QVector<CommentSpan> comments = findComments(text);

QString code(text);

    // blank the comments out, the word patterns all stop at a space
    for (const CommentSpan &comment : comments)
        code.replace(comment.start, comment.length, QString(comment.length, QLatin1Char(' ')));

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    for (const HighlightingRule &rule : highlightingRules)
        {
        QRegularExpressionMatchIterator it = rule.pattern.globalMatch(code);
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
        int index = expression.indexIn(code);
        while (index >= 0)
            {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(code, index + length);
            }
        }
#endif

    for (const CommentSpan &comment : comments)
        setFormat(comment.start, comment.length,
                  comment.semicolon ? semicolonCommentFormat : braceCommentFormat);

    setCurrentBlockState(0);
}