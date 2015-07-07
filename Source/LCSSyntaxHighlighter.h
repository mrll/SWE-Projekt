//
// Created by Matthias Röll, Marc Wüst
//
// Code Example from http://doc.qt.io/qt-4.8/qt-richtext-syntaxhighlighter-example.html

#ifndef LCSSYNTAXHIGHLIGHTER_H
#define LCSSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

#include <QHash>
#include <QTextCharFormat>

class QTextDocument;

/**
 * @brief Syntax Highlighter für den Code Editor
 *
 * Die Klasse basiert auf dem QT-Beispielcode von:
 * http://doc.qt.io/qt-4.8/qt-richtext-syntaxhighlighter-example.html
 */
class LCSSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    LCSSyntaxHighlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text);

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QTextCharFormat keywordFormat;
    QTextCharFormat parameterFormat;
    QTextCharFormat commentFormat;
};


#endif //LCSSyntaxHighlighter_H
