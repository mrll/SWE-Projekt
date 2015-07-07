#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "LCSSyntaxHighlighter.h"
#include "LCSGridGraphicScene.h"

#include <QFileDialog>
#include <QTextDocumentWriter>
#include <QTextStream>
#include <QTime>

/* ---------------------------------------------------------------------------------------------------------------- */
/* Delay Funktion (für Animation)                                                                                   */
/* ---------------------------------------------------------------------------------------------------------------- */

void delay(double seconds) {
    // Delay Funktion ohne UserInterface unterbrechung
    QTime dieTime= QTime::currentTime().addMSecs((int)(seconds * 1000));
    while( QTime::currentTime() < dieTime ) {
        // Events weithin ausführen
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

/* ---------------------------------------------------------------------------------------------------------------- */
/* GUI View Controller                                                                                              */
/* ---------------------------------------------------------------------------------------------------------------- */

/* ======================= */
/* Konstruktor             */
/* ======================= */

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->tabWidget->setCurrentWidget(ui->codeTab);

    // Steuercode Inputs
    connect(ui->openButton, SIGNAL(clicked()), this, SLOT(openButtonAction()));
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveButtonAction()));

    connect(ui->codeEdit, SIGNAL(textChanged()), this, SLOT(codeChangedAction()));
    connect(ui->codeEdit, SIGNAL(cursorPositionChanged()), this, SLOT(codeCursorChangedAction()));

    // Simulation Inputs
    connect(ui->runCodeButton,  SIGNAL(clicked()), this, SLOT(runAutomaticAction()));
    connect(ui->stopCodeButton, SIGNAL(clicked()), this, SLOT(stopAutomaticAction()));

    connect(ui->stepDelaySpinner, SIGNAL(valueChanged(double)), this, SLOT(stepDelaySpinnerAction()));
    connect(ui->drawDelaySpinner, SIGNAL(valueChanged(double)), this, SLOT(drawDelaySpinnerAction()));

    connect(ui->gridSizeSpinner, SIGNAL(valueChanged(int)),     this, SLOT(gridSizeSpinnerAction()));

    // Grid Scene
    _syntaxHighlighter  = new LCSSyntaxHighlighter(ui->codeEdit->document());
    _graphicsScene      = new LCSGridGraphicScene(this);
    ui->simGView->setScene(_graphicsScene);

    ui->runCodeButton->setEnabled(true);
    ui->stopCodeButton->setEnabled(false);

    setDrawAnimationTime(2);
    setStepAnimationTime(0.5);

    _proceedExec = true;
}

MainWindow::~MainWindow() {
    delete ui;
}

/* ======================= */
/* Öffnen & Speichern      */
/* ======================= */

void MainWindow::openButtonAction() {
    // Open Dialog erstellen und ausführen
    QString fn = QFileDialog::getOpenFileName(this, tr("Datei oeffnen..."),
                                              QString(), tr("Text Dateien (*.txt);;Alle Dateien (*)"));
    // Datei laden
    if (!fn.isEmpty()) {
        QFile textFile(fn);
        textFile.open(QFile::ReadOnly | QFile::Text);
        QTextStream fileStream(&textFile);
        ui->codeEdit->setPlainText(fileStream.readAll());
    }
}

void MainWindow::saveButtonAction() {
    // SaveDialog erstellen und ausführen
    QString fn = QFileDialog::getSaveFileName(this, tr("Speichern unter..."),
                                              QString(), tr("Text Datei (*.txt)"));
    // Dateisuffix anhängen
    if (!fn.isEmpty()) {
        if (!fn.endsWith(".txt", Qt::CaseInsensitive)) {
            fn += ".txt"; // default
        }
    }

    // Datei schreiben
    QTextDocumentWriter writer(fn);
    bool success = writer.write(ui->codeEdit->document());
    if (success) {
        ui->codeEdit->document()->setModified(false);
    }
}

/* ======================= */
/* Editor Änderungen       */
/* ======================= */

void MainWindow::codeChangedAction() {
    // Code parsen
    bool success = _laser.parseInstructionCode(ui->codeEdit->document()->toPlainText().toStdString());

    // Log String erstellen (für Fehlermeldungsfenster)
    QString logString;
    std::vector<LCSParserCommand> commands = _laser.commands();
    std::vector<LCSParserError>   errors   = _laser.errors();

    logString =  "Befehle: " + QString::number(commands.size()) + "\n";
    logString += "Fehler: "  + QString::number(errors.size()) + "\n";
    logString += "-------------------------------\n";

    if (success) {
        logString += "Code in Ordnung";

        // Sim Interface
        ui->runCodeButton->setEnabled(true);
        ui->codeLogLabel->setText("Code OK!");
    } else {
        logString += "Fehlermeldungen:\n\n";

        // Fehlermeldungen sammeln
        for (size_t i = 0; i < errors.size(); i++) {
            logString += "Zeile: " + QString::number(errors.at(i).line)  + "\n";
            logString += "Code:\n" + QString(errors.at(i).code.c_str()) + "\n\n";
        }

        // Sim Interface
        ui->runCodeButton->setEnabled(false);
        ui->codeLogLabel->setText("Code nicht OK!");
    }

    // Sonstige UI Werte setzen
    ui->cmdCountLabel->setText(QString::number(commands.size()));
    ui->codeLog->document()->setPlainText(logString);

    LCSPoint codeSize = _laser.codeGridSize();
    ui->codeSizeLabel->setText(QString::number(codeSize.x) + " x " + QString::number(codeSize.y));

    laserUpdate();
}

void MainWindow::codeCursorChangedAction() {
    // Aktuelle Zeile Highlighten
    QTextEdit::ExtraSelection highlight;
    highlight.cursor = ui->codeEdit->textCursor();
    highlight.format.setProperty(QTextFormat::FullWidthSelection, true);
    highlight.format.setBackground(Qt::lightGray);

    QList<QTextEdit::ExtraSelection> extras;
    extras << highlight;
    ui->codeEdit->setExtraSelections(extras);
}

/* ======================= */
/* Befehlsausführung       */
/* ======================= */

void MainWindow::runAutomaticAction() {
    // Grid löschen
    _graphicsScene->clear();
    _proceedExec = true;
    // UI Buttons de-/aktivieren
    ui->stopCodeButton->setEnabled(true);
    ui->runCodeButton->setEnabled(false);
    // Ausführung starten
    _laser.runInstructions(ui->relativeRadioButton->isChecked(), this);
}

void MainWindow::stopAutomaticAction() {
    // Abbruchvariable setzen
    _proceedExec = false;
    // UI Buttons de-/aktivieren
    ui->runCodeButton->setEnabled(true);
    ui->stopCodeButton->setEnabled(false);
}

/* ======================= */
/* Animationszeiten Events */
/* ======================= */

void MainWindow::drawDelaySpinnerAction() {
    _drawAnimationTime = ui->drawDelaySpinner->value();
}

void MainWindow::stepDelaySpinnerAction() {
    _stepAnimationTime = ui->stepDelaySpinner->value();
}

/* ======================= */
/* Grid Abstand Event      */
/* ======================= */

void MainWindow::gridSizeSpinnerAction() {
    _graphicsScene->setGridStep(ui->gridSizeSpinner->value());
    ui->simGView->update();
}

/* ======================= */
/* LCSSimulationInterface  */
/* ======================= */

void MainWindow::drawLine(LCSPoint from, LCSPoint to) {
    // Schwarzer 'Stift' (static da immer wieder benutzt)
    static QPen pen(QBrush(Qt::black, Qt::SolidPattern), 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    // Startpunkt erstellen
    QPoint stepPoint = QPoint(from.x, from.y);
    // Schritte für die Animation erstellen
    double xStep = (to.x - from.x) / 10.0;
    double yStep = (to.y - from.y) / 10.0;

    // Linie Schrittweise malen (Animation)
    for (int i = 0; i < 9; ++i) {
        _graphicsScene->addLine(stepPoint.x(), stepPoint.y(), stepPoint.x() + xStep, stepPoint.y() + yStep, pen);
        // Weitere Ausführung Verzögern
        delay(drawAnimationTime() / 10.0);
        // Schritte addieren
        stepPoint.setX((int) (stepPoint.x() + xStep));
        stepPoint.setY((int) (stepPoint.y() + yStep));
        // Laserpositionslabel aktualisieren
        ui->laserPosXLabel->setText(QString::number(stepPoint.x()));
        ui->laserPosYLabel->setText(QString::number(stepPoint.y()));
    }
    // Den letzten Schritt mit den Zielwerten zeichnen, da sonst eine Ungenauigkeit durch stepPoint entstehen kann
    _graphicsScene->addLine(stepPoint.x(), stepPoint.y(), to.x, to.y, pen);
    delay(drawAnimationTime() / 10.0);

    ui->laserPosXLabel->setText(QString::number(stepPoint.x()));
    ui->laserPosYLabel->setText(QString::number(stepPoint.y()));
}

void MainWindow::laserUpdate() {
    // Laserstatus aktualisieren
    if (_laser.isLaserOn()) {
        ui->laserOnStateLabel->setText("AN");
    } else {
        ui->laserOnStateLabel->setText("AUS");
    }
    // Motorstatus aktualisieren
    if (_laser.isMoving()) {
        ui->laserMoveStateLabel->setText("MOVE");
    } else {
        ui->laserMoveStateLabel->setText("HALT");
    }

    // Aktuellen Befehl aktualisieren
    LCSParserCommand cmd = _laser.currentCommand();
    // Kein Befehl
    if (cmd.command == LCSCmdUnknown) {
        ui->commandLineLabel->setText("");
        ui->commandLabel->setText("NONE");
    } else {
        // Zeilennummer
        ui->commandLineLabel->setText("Zeile: " + QString::number(cmd.line));
        // Move Befehl
        if (cmd.command == LCSCmdEngine) {
            ui->commandLabel->setText("MOVE " + QString::number(cmd.parameter[0]) + ", " + QString::number(cmd.parameter[1]));
        // Laser Befehl
        } else if (cmd.command == LCSCmdLaser) {
            if (cmd.parameter[0]) {
                ui->commandLabel->setText("LASER ON");
            } else {
                ui->commandLabel->setText("LASER OFF");
            }
        // Unbekannter Befehl
        } else {
            ui->commandLabel->setText("Unbekannter Befehl");
        }
    }

    // Laserposition aktualisieren
    ui->laserPosXLabel->setText(QString::number(_laser.actualPosition().x));
    ui->laserPosYLabel->setText(QString::number(_laser.actualPosition().y));

    // Kurz Warten da sonst einige Aktualisierungen wärend der Ausführung
    // zu schnell wieder verschwinden
    delay(_stepAnimationTime);
}

bool MainWindow::proceedExecution() {
    return _proceedExec;
}

void MainWindow::finishedExecution() {
    ui->runCodeButton->setEnabled(true);
    ui->stopCodeButton->setEnabled(false);
}

/* ======================= */
/* Getter und Setter       */
/* ======================= */

double MainWindow::drawAnimationTime() {
    return _drawAnimationTime;
}

void MainWindow::setDrawAnimationTime(double timeInSeconds) {
    _drawAnimationTime = timeInSeconds;
    ui->drawDelaySpinner->setValue(timeInSeconds);
}

double MainWindow::stepAnimationTime() {
    return _stepAnimationTime;
}

void MainWindow::setStepAnimationTime(double timeInSeconds) {
    _stepAnimationTime = timeInSeconds;
    ui->stepDelaySpinner->setValue(timeInSeconds);
}
