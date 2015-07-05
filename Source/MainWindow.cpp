#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "LCSSyntaxHighlighter.h"
#include "LCSGridGraphicScene.h"

#include <QFileDialog>
#include <QTextDocumentWriter>
#include <QTextStream>
#include <QTime>

void delay(double seconds) {
    // Delay Funktion ohne UserInterface unterbrechung
    QTime dieTime= QTime::currentTime().addMSecs((int)(seconds * 1000));
    while( QTime::currentTime() < dieTime ) {
        // Events weithin ausführen
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->tabWidget->setCurrentWidget(ui->codeTab);

    // Steuercode Inputs
    connect(ui->openButton, SIGNAL(clicked()), this, SLOT(openButtonAction()));
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveButtonAction()));

    connect(ui->codeEdit, SIGNAL(textChanged()), this, SLOT(codeChangedAction()));
    connect(ui->codeEdit, SIGNAL(cursorPositionChanged()), this, SLOT(codeCursorChangedAction()));

    // Simualtion Inputs
    connect(ui->runCodeButton, SIGNAL(clicked()), this, SLOT(runAutomaticAction()));

    // Grid Scene
    _syntaxHighlighter  = new LCSSyntaxHighlighter(ui->codeEdit->document());
    _graphicsScene      = new LCSGridGraphicScene(this);
    ui->simGView->setScene(_graphicsScene);

    setDrawAnimationTime(2);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openButtonAction() {
    QString fn = QFileDialog::getOpenFileName(this, tr("Datei oeffnen..."),
                                              QString(), tr("Text Dateien (*.txt);;Alle Dateien (*)"));
    if (!fn.isEmpty()) {
        QFile textFile(fn);
        textFile.open(QFile::ReadOnly | QFile::Text);
        QTextStream fileStream(&textFile);
        ui->codeEdit->setPlainText(fileStream.readAll());
    }
}

void MainWindow::saveButtonAction() {
    QString fn = QFileDialog::getSaveFileName(this, tr("Speichern unter..."),
                                              QString(), tr("Text Datei (*.txt)"));

    if (!fn.isEmpty()) {
        if (!fn.endsWith(".txt", Qt::CaseInsensitive)) {
            fn += ".txt"; // default
        }
    }

    QTextDocumentWriter writer(fn);
    bool success = writer.write(ui->codeEdit->document());
    if (success) {
        ui->codeEdit->document()->setModified(false);
    }
}

void MainWindow::codeChangedAction() {
    // Code parsen
    bool success = this->_laser.parseInstructionCode(ui->codeEdit->document()->toPlainText().toStdString());

    // Log String
    QString logString;
    std::vector<LCSParserCommand> commands = this->_laser.commands();
    std::vector<LCSParserError>   errors   = this->_laser.errors();

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

    ui->cmdCountLabel->setText(QString::number(commands.size()));
    ui->codeLog->document()->setPlainText(logString);

    LCSPoint codeSize = this->_laser.codeGridSize();
    ui->codeSizeLabel->setText(QString::number(codeSize.x) + " x " + QString::number(codeSize.y));

    this->laserUpdate();
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

void MainWindow::runAutomaticAction() {
    // Grid löschen und Laser starten
    _graphicsScene->clear();
    this->_laser.runInstructions(ui->relativeRadioButton->isChecked(), this);
}

void MainWindow::drawLine(LCSPoint from, LCSPoint to) {
    static QPen pen(QBrush(Qt::black, Qt::SolidPattern), 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    QPoint stepPoint = QPoint(from.x, from.y);
    double xStep = (to.x - from.x) / 10.0;
    double yStep = (to.y - from.y) / 10.0;

    // Linie Schrittweise malen (Animationszwecke)
    for (int i = 0; i < 10; ++i) {
        _graphicsScene->addLine(stepPoint.x(), stepPoint.y(), stepPoint.x() + xStep, stepPoint.y() + yStep, pen);
        delay(drawAnimationTime() / 10.0);
        stepPoint.setX((int) (stepPoint.x() + xStep));
        stepPoint.setY((int) (stepPoint.y() + yStep));

        ui->laserPosXLabel->setText(QString::number(stepPoint.x()));
        ui->laserPosYLabel->setText(QString::number(stepPoint.y()));
    }
}

void MainWindow::laserUpdate() {
    if (this->_laser.isLaserOn()) {
        ui->laserOnStateLabel->setText("AN");
    } else {
        ui->laserOnStateLabel->setText("AUS");
    }

    if (this->_laser.isMoving()) {
        ui->laserMoveStateLabel->setText("MOVE");
    } else {
        ui->laserMoveStateLabel->setText("HALT");
    }

    LCSParserCommand cmd = this->_laser.currentCommand();
    // Kein Befehl
    if (cmd.command == LCSCmdUnknown) {
        ui->commandLineLabel->setText("");
        ui->commandLabel->setText("NONE");
    } else {
        // Zeilennummer
        ui->commandLineLabel->setText("Line " + QString::number(cmd.line) + ":");
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

    // Kurz Warten da sonst einige Aktualisierungen nicht sichtbar sind
    delay(this->_drawAnimationTime / 4.0);
}

int MainWindow::drawAnimationTime() {
    return _drawAnimationTime;
}

void MainWindow::setDrawAnimationTime(int timeInSeconds) {
    _drawAnimationTime = timeInSeconds;
}
