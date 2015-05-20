//
// Created by Matthias Röll on 10.05.15.
//

#include "LCUserInterface.h"
#include "../Model/LCParser.h"

#include <QFileDialog>
#include <QTextDocumentWriter>
#include <QTextStream>

#pragma mark De-/Konstruktor

LCUserInterface::LCUserInterface(QMainWindow *parent) {
    setupUi(this);

    tabWidget->setCurrentWidget(codeTab);

    // Steuercode Inputs
    connect(openButton, SIGNAL(clicked()), this, SLOT(openButtonAction()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveButtonAction()));

    connect(codeEdit, SIGNAL(textChanged()), this, SLOT(codeChangedAction()));
    connect(codeEdit, SIGNAL(cursorPositionChanged()), this, SLOT(codeCursorChangedAction()));

    // Simualtion Inputs
    connect(runCodeButton, SIGNAL(clicked()), this, SLOT(runAutomaticAction()));

    connect(manualLaserMoveButton, SIGNAL(clicked()), this, SLOT(runManualAction()));
    connect(manualLaserStateButton, SIGNAL(clicked()), this, SLOT(toggleLaserAction()));

    syntaxHighlighter = new LCSyntaxHighlighter(codeEdit->document());

    relativeRadioButton->setEnabled(false); // Vorerst deaktiviert
}

LCUserInterface::~LCUserInterface() {
}

#pragma mark Steuercode Tab Actions

void LCUserInterface::openButtonAction() {
    QString fn = QFileDialog::getOpenFileName(this, tr("Datei öffnen..."),
                                              QString(), tr("Text Dateien (*.txt);;Alle Dateien (*)"));
    if (!fn.isEmpty()) {
        QFile textFile(fn);
        textFile.open(QFile::ReadOnly | QFile::Text);
        QTextStream fileStream(&textFile);
        codeEdit->setPlainText(fileStream.readAll());
    }
}

void LCUserInterface::saveButtonAction() {
    QString fn = QFileDialog::getSaveFileName(this, tr("Speichern unter..."),
                                              QString(), tr("Text Datei (*.txt)"));

    if (!fn.isEmpty()) {
        if (!fn.endsWith(".txt", Qt::CaseInsensitive)) {
            fn += ".txt"; // default
        }
    }

    QTextDocumentWriter writer(fn);
    bool success = writer.write(codeEdit->document());
    if (success) {
        codeEdit->document()->setModified(false);
    }
}

void LCUserInterface::codeChangedAction() {
    static LCParser parser = LCParser();

    QVector<LCParserCommand> commands = QVector<LCParserCommand>();
    QVector<LCParserError> errors = QVector<LCParserError>();

    QString logString;

    if(parser.parse(codeEdit->document()->toPlainText(), &commands, &errors)) {
        // Log String
        logString =  "Befehle: "+ QString::number(commands.count()) + "\n";
        logString += "Fehler: 0\n";
        logString += "-------------------------------\n";
        logString += "Code in Ordnung";

        // Sim Interface
        runCodeButton->setEnabled(true);
        codeLogLabel->setText("Code OK!");
    } else {
        // Log String
        logString =  "Befehle: " + QString::number(commands.count()) + "\n";
        logString += "Fehler: "  + QString::number(errors.count()) + "\n";
        logString += "-------------------------------\n";
        logString += "Fehlermeldungen:\n\n";

        for (int i = 0; i < errors.count(); ++i) {
            logString += "Zeile: " + QString::number(errors.at(i).line)  + "\n";
            logString += "Meldung:\n" + errors.at(i).error + "\n\n";
        }

        // Sim Interface
        runCodeButton->setEnabled(false);
        codeLogLabel->setText("Code nicht OK!");
    }

    cmdCountLabel->setText(QString::number(commands.count()));
    codeLog->document()->setPlainText(logString);
}

void LCUserInterface::codeCursorChangedAction() {
    QTextEdit::ExtraSelection highlight;
    highlight.cursor = codeEdit->textCursor();
    highlight.format.setProperty(QTextFormat::FullWidthSelection, true);
    highlight.format.setBackground(Qt::lightGray);

    QList<QTextEdit::ExtraSelection> extras;
    extras << highlight;
    codeEdit->setExtraSelections(extras);
}

#pragma mark Simulation Tab Actions

void LCUserInterface::runAutomaticAction() {

}

void LCUserInterface::runManualAction() {

}

void LCUserInterface::toggleLaserAction() {

}

#pragma mark Simulation Drawing

void LCUserInterface::drawLine(QPoint from, QPoint to) {
}

float LCUserInterface::drawAnimationTime() {
    return _drawAnimationTime;
}

void LCUserInterface::setDrawAnimationTime(float timeInSeconds) {
    _drawAnimationTime = timeInSeconds;
}
