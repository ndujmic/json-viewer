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
    void appendNewRule(QString exp, QColor color);

    struct HighlightingRule
         {
             QString pattern;
             QTextCharFormat format;
         };
         QVector<HighlightingRule> rules;
protected:
    void highlightBlock(const QString &text);
};


#endif // JSONHIGHLIGHTER_H
