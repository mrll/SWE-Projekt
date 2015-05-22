//
// Created by Matthias Röll on 10.05.15.
//

#include "LCUserInterface.h"
#include "../Model/LCParser.h"

#include <QFileDialog>
#include <QTextDocumentWriter>
#include <QTextStream>
#include <QTime>

static QVector<LCParserCommand> commands = QVector<LCParserCommand>();
static QVector<LCParserError> errors = QVector<LCParserError>();

#pragma mark Delay Funktion

void delay(double seconds)
{
    QTime dieTime= QTime::currentTime().addMSecs((int)(seconds * 1000));
    while( QTime::currentTime() < dieTime ) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

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

    // Grid Scene
    _syntaxHighlighter  = new LCSyntaxHighlighter(codeEdit->document());
    _graphicsScene      = new LCGridGraphicScene(this);
    simGView->setScene(_graphicsScene);

    setDrawAnimationTime(2);
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

    QPoint minPos(0, 0), maxPos(0, 0);

    commands.clear();
    errors.clear();

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

    for (int j = 0; j < commands.count(); ++j) {
        if (commands.at(j).command == LCMoveCommand) {
            if (commands.at(j).parameter[0] < minPos.x()) {
                minPos.setX(commands.at(j).parameter[0]);
            } else if (commands.at(j).parameter[0] > maxPos.x()) {
                maxPos.setX(commands.at(j).parameter[0]);
            }

            if (commands.at(j).parameter[1] < minPos.y()) {
                minPos.setY(commands.at(j).parameter[1]);
            } else if (commands.at(j).parameter[1] > maxPos.y()) {
                maxPos.setY(commands.at(j).parameter[1]);
            }
        }
    }

    codeSizeLabel->setText(QString::number(maxPos.x() - minPos.x()) + ", " + QString::number(maxPos.y() - minPos.y()));

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
    _graphicsScene->clear();

    bool laserOn = false;
    QPoint currentPosition(0, 0);
    for (int i = 0; i < commands.count(); ++i) {
        commandLineLabel->setText(QString::number(commands.at(i).line));

        if (commands.at(i).command == LCPowerCommand) {
            laserMoveStateLabel->setText("Stand");

            if (commands.at(i).parameter[0]) {
                commandLabel->setText("LASER ON");
                laserOnStateLabel->setText("An");
                laserOn = true;
            } else {
                commandLabel->setText("LASER OFF");
                laserOnStateLabel->setText("Aus");
                laserOn = false;
            }
        } else if (commands.at(i).command == LCMoveCommand) {
            laserMoveStateLabel->setText("Fahren");

            commandLabel->setText("MOVE " + QString::number(commands.at(i).parameter[0]) + ", " + QString::number(commands.at(i).parameter[1]));

            if (laserOn) {
                if (relativeRadioButton->isChecked()) {
                    drawLine(currentPosition, QPoint(currentPosition.x() + commands.at(i).parameter[0],
                                                     currentPosition.y() + commands.at(i).parameter[1]));

                    currentPosition.setX(currentPosition.x() + commands.at(i).parameter[0]);
                    currentPosition.setY(currentPosition.y() + commands.at(i).parameter[1]);
                } else {
                    drawLine(currentPosition, QPoint(commands.at(i).parameter[0],
                                                     commands.at(i).parameter[1]));

                    currentPosition.setX(commands.at(i).parameter[0]);
                    currentPosition.setY(commands.at(i).parameter[1]);
                }

            }
        }

        laserPosXLabel->setText(QString::number(currentPosition.x()));
        laserPosYLabel->setText(QString::number(currentPosition.y()));
    }
}

void LCUserInterface::runManualAction() {

}

void LCUserInterface::toggleLaserAction() {

}

#pragma mark Simulation Drawing

void LCUserInterface::drawLine(QPoint from, QPoint to) {
    static QPen pen(QBrush(Qt::black, Qt::SolidPattern), 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    QPoint stepPoint = from;
    double xStep = (to.x() - from.x()) / 10.0;
    double yStep = (to.y() - from.y()) / 10.0;

    for (int i = 0; i < 10; ++i) {
        _graphicsScene->addLine(stepPoint.x(), stepPoint.y(), stepPoint.x() + xStep, stepPoint.y() + yStep, pen);
        delay(drawAnimationTime() / 10.0);
        stepPoint.setX((int) (stepPoint.x() + xStep));
        stepPoint.setY((int) (stepPoint.y() + yStep));
    }
}

int LCUserInterface::drawAnimationTime() {
    return _drawAnimationTime;
}

void LCUserInterface::setDrawAnimationTime(int timeInSeconds) {
    _drawAnimationTime = timeInSeconds;
}
