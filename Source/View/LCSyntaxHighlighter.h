//
// Created by Matthias Röll on 20.05.15.
//
// Code Example from http://doc.qt.io/qt-4.8/qt-richtext-syntaxhighlighter-example.html

#ifndef SWE_PROJEKT_LCSYNTAXHIGHLIGHTER_H
#define SWE_PROJEKT_LCSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

#include <QHash>
#include <QTextCharFormat>

class QTextDocument;

class LCSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    LCSyntaxHighlighter(QTextDocument *parent = 0);

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


#endif //SWE_PROJEKT_LCSYNTAXHIGHLIGHTER_H
