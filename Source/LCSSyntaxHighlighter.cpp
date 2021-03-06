//
// Created by Matthias Röll, Marc Wüst
//
// Code Example from http://doc.qt.io/qt-4.8/qt-richtext-syntaxhighlighter-example.html

#include "LCSSyntaxHighlighter.h"

#include <QtGui>

/* ---------------------------------------------------------------------------------------------------------------- */
/* Syntax highlighter                                                                                               */
/* ---------------------------------------------------------------------------------------------------------------- */

/* ======================= */
/* Konstruktor             */
/* ======================= */

LCSSyntaxHighlighter::LCSSyntaxHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent) {
    HighlightingRule rule;

    // Keyword Highlight Patterns (MOVE, LASER)
    keywordFormat.setForeground(Qt::darkMagenta);
    keywordFormat.setFontWeight(QFont::Bold);

    QStringList keywordPatterns;
    keywordPatterns << "\\bMOVE\\b" << "\\bLASER\\b";

    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern, Qt::CaseInsensitive, QRegExp::RegExp);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // Parameter Highlight Pattern (0 - 9999 and ON, OFF)
    parameterFormat.setForeground(Qt::darkBlue);

    rule.pattern = QRegExp("\\b(\\d{1,4})\\b", Qt::CaseInsensitive, QRegExp::RegExp);
    rule.format = parameterFormat;
    highlightingRules.append(rule);

    rule.pattern = QRegExp("\\b(ON|OFF)\\b", Qt::CaseInsensitive, QRegExp::RegExp);
    rule.format = parameterFormat;
    highlightingRules.append(rule);

    // Comment Pattern (# ...)
    commentFormat.setFontItalic(true);
    commentFormat.setForeground(Qt::darkGreen);

    rule.pattern = QRegExp("\\s?\\#+.*$", Qt::CaseInsensitive, QRegExp::RegExp);
    rule.format = commentFormat;
    highlightingRules.append(rule);
}

/* ======================= */
/* Highlighter             */
/* ======================= */

void LCSSyntaxHighlighter::highlightBlock(const QString &text) {
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);

        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
    setCurrentBlockState(0);

}
