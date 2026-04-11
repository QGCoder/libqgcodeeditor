#include <QSyntaxHighlighter>

#include <QHash>
#include <QTextCharFormat>

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QRegularExpression>
#define QRegExp QRegularExpression
#else
#include <QRegExp>
#endif

class QGCodeSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    QGCodeSyntaxHighlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;

private:
    struct HighlightingRule
        {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        QRegularExpression pattern;
#else
        QRegExp pattern;
#endif
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
