#include "jsonhighlighter.h"
#include <QRegExp>
#include <QDebug>
#include <QTextCharFormat>
#include <QQuickTextDocument>
#include <QRegularExpressionMatchIterator>

JSONHighlighter::JSONHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{

    // number value
    appendNewRule(QString("[^\"]([-0-9.]+)[^\"]"), QColor(QString("DeepPink")));

    // string value
    appendNewRule(QString(":\\s*([\"](?:[^\"])*[\"])"), QColor(QString("OrangeRed")));

    // key
    appendNewRule(QString("(\"[^\"]*\")[:]"), QColor(QString("Green")));

    // true/false values
    appendNewRule(QString("([^\"]true|[^\"]false)(?!\"[^\"]*\")"), QColor(QString("Orange")));

    // null value
    appendNewRule(QString("([^\"]null)(?!\"[^\"]*\")"), QColor(QString("RoyalBlue")));

}

void JSONHighlighter::highlightBlock(const QString &text)
{
     foreach (const HighlightingRule &rule, rules) {
        QRegularExpression expression(rule.pattern);
        QRegularExpressionMatchIterator i = expression.globalMatch(text);

        while (i.hasNext()) {
            QRegularExpressionMatch match = i.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
     }
}

void JSONHighlighter::appendNewRule(QString exp, QColor color) {
    HighlightingRule rule;

    rule.pattern = exp;
    rule.format.setForeground(color);
    rules.append(rule);
}


