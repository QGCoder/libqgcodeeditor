#include <QSyntaxHighlighter>

#include <QHash>
#include <QTextCharFormat>

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
