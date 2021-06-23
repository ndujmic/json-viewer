#ifndef JSONHIGHLIGHTER_H
#define JSONHIGHLIGHTER_H

#include <QObject>

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QQuickTextDocument>

class JSONHighlighter: public QSyntaxHighlighter
{
public:
    JSONHighlighter(QTextDocument *parent = 0);

private:
    void appendNewRule(QRegExp exp, QColor color);

    struct HighlightingRule
         {
             QRegExp pattern;
             QTextCharFormat format;
         };
         QVector<HighlightingRule> rules;
protected:
    void highlightBlock(const QString &text);
};


#endif // JSONHIGHLIGHTER_H
