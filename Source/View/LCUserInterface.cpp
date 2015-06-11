//
// Created by Matthias Röll on 10.05.15.
//

#include "LCUserInterface.h"
#include "../Controller/LCController.h"

#include <QFileDialog>
#include <QTextDocumentWriter>
#include <QTextStream>
#include <QTime>

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
    controller = NULL;
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
    if (controller != NULL) {
        bool                     success  = controller->updateCode(codeEdit->document()->toPlainText());
        QVector<LCParserCommand> commands = controller->getCommands();
        QVector<LCParserError>   errors   = controller->getErrors();

        // Log String
        QString logString;
        logString =  "Befehle: " + QString::number(commands.count()) + "\n";
        logString += "Fehler: "  + QString::number(errors.count()) + "\n";
        logString += "-------------------------------\n";

        if(success) {
            logString += "Code in Ordnung";

            // Sim Interface
            runCodeButton->setEnabled(true);
            codeLogLabel->setText("Code OK!");
        } else {
            logString += "Fehlermeldungen:\n\n";

            for (int i = 0; i < errors.count(); i++) {
                logString += "Zeile: " + QString::number(errors.at(i).line)  + "\n";
                logString += "Meldung:\n" + errors.at(i).error + "\n\n";
            }

            // Sim Interface
            runCodeButton->setEnabled(false);
            codeLogLabel->setText("Code nicht OK!");
        }

        QPoint size = controller->getCodeDrawSize();
        codeSizeLabel->setText(QString::number(size.x()) + ", " + QString::number(size.y()));
        cmdCountLabel->setText(QString::number(commands.count()));
        codeLog->document()->setPlainText(logString);
    }
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

    if (_controller != NULL) {

        /*if (_controller->getErrors().count() == 0) {
            return;
        }*/

        LCLaser                     laser       = _controller->getLaser();
        QVector<LCParserCommand>    commands    = _controller->getCommands();

        for (int i = 0; i < commands.count(); ++i) {
            commandLineLabel->setText(QString::number(commands.at(i).line));

            if (commands.at(i).command == LCPowerCommand) {
                laserMoveStateLabel->setText("Stand");
                laser.halt();

                if (commands.at(i).parameter[0]) {
                    commandLabel->setText("LASER ON");
                    laserOnStateLabel->setText("An");
                    laser.on();
                } else {
                    commandLabel->setText("LASER OFF");
                    laserOnStateLabel->setText("Aus");
                    laser.off();
                }
            } else if (commands.at(i).command == LCMoveCommand) {
                laserMoveStateLabel->setText("Fahren");
                laser.move();

                commandLabel->setText("MOVE " + QString::number(commands.at(i).parameter[0]) + ", " + QString::number(commands.at(i).parameter[1]));

                if (laser.isOn()) {
                    // Zeichnen und Position aktualisieren (Wird in drawLine aktualisiert)
                    if (relativeRadioButton->isChecked()) {
                        drawLine(laser.actualPosition(), QPoint(laser.actualPosition().x() + commands.at(i).parameter[0],
                                                                laser.actualPosition().y() + commands.at(i).parameter[1]));
                    } else {
                        drawLine(laser.actualPosition(), QPoint(commands.at(i).parameter[0],
                                                                commands.at(i).parameter[1]));
                    }
                } else {
                    // Nur Position aktualisieren
                    if (relativeRadioButton->isChecked()) {
                        laser.setActualPosition(QPoint(laser.actualPosition().x() + commands.at(i).parameter[0],
                                                       laser.actualPosition().y() + commands.at(i).parameter[1]));
                    } else {
                        laser.setActualPosition(QPoint(commands.at(i).parameter[0],
                                                       commands.at(i).parameter[1]));
                    }
                }
            }

            laserPosXLabel->setText(QString::number(laser.actualPosition().x()));
            laserPosYLabel->setText(QString::number(laser.actualPosition().y()));
        }


        laserMoveStateLabel->setText("Stand");
        laser.halt();
    }
}

void LCUserInterface::runManualAction() {
    if (_controller != NULL) {
        laserMoveStateLabel->setText("Fahren");
        _controller->getLaser().move();

        if (_controller->getLaser().isOn()) {
            // Zeichnen und Position aktualisieren (Wird in drawLine aktualisiert)
            drawLine(_controller->getLaser().actualPosition(), QPoint(manualPositionXInput->text().toInt(),
                                                                      manualPositionYInput->text().toInt()));
        } else {
            // Nur Position aktualisieren
            _controller->getLaser().setActualPosition(QPoint(manualPositionXInput->text().toInt(),
                                                             manualPositionYInput->text().toInt()));
        }

        laserPosXLabel->setText(QString::number(_controller->getLaser().actualPosition().x()));
        laserPosYLabel->setText(QString::number(_controller->getLaser().actualPosition().y()));

        laserMoveStateLabel->setText("Stand");
        _controller->getLaser().halt();
    }
}

void LCUserInterface::toggleLaserAction() {
    if (_controller != NULL) {
        if (_controller->getLaser().isOn()) {
            _controller->getLaser().off();
            laserOnStateLabel->setText("Aus");
        } else {
            _controller->getLaser().on();
            laserOnStateLabel->setText("An");
        }
    }
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
        if (_controller != NULL) {
            _controller->getLaser().setActualPosition(stepPoint);
            laserPosXLabel->setText(QString::number(stepPoint.x()));
            laserPosYLabel->setText(QString::number(stepPoint.y()));
        }
    }
}

int LCUserInterface::drawAnimationTime() {
    return _drawAnimationTime;
}

void LCUserInterface::setDrawAnimationTime(int timeInSeconds) {
    _drawAnimationTime = timeInSeconds;
}
