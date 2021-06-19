#include "jsonhighlighter.h"
#include <QRegExp>
#include <QDebug>
#include <QTextCharFormat>
#include <QQuickTextDocument>

JSONHighlighter::JSONHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    // number value
    rule.pattern = QRegExp("[^\"]([-0-9.]+)(?!([^\"]*\"[\\s]*\\:))");
    rule.format.setForeground(QColor(255, 0, 110));
    rules.append(rule);

    // key
    rule.pattern = QRegExp("(\"[^\"]*\")[:]");
    rule.format.setForeground(QColor(131, 56, 236));
    rules.append(rule);

    // string value
//    rule.pattern = QRegExp(":\\s*([\"](?:[^\"])*[\"])");
        rule.pattern = QRegExp(":\\s*([\"](?:[^\"])*[\"])");
    rule.format.setForeground(QColor(251, 86, 7));
    rules.append(rule);

    // true/false values
    rule.pattern = QRegExp("([^\"]true|[^\"]false)(?!\"[^\"]*\")");
    rule.format.setForeground(QColor(255, 190, 11));
    rules.append(rule);

    // null value
    rule.pattern = QRegExp("([^\"]null)(?!\"[^\"]*\")");
    rule.format.setForeground(QColor(58, 134, 255));
    rules.append(rule);
}

void JSONHighlighter::highlightBlock(const QString &text)
{
     foreach (const HighlightingRule &rule, rules) {
         QRegExp expression(rule.pattern);
         int index = expression.indexIn(text);

         while (index >= 0) {
             index = expression.pos(1);
             int length = expression.cap(1).length();
             setFormat(index, length, rule.format);
             index = expression.indexIn(text, index + length);
         }
     }
}
