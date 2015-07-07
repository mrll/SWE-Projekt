//
// Created by Matthias Röll, Marc Wüst
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "LCSSyntaxHighlighter.h"
#include "LCSGridGraphicScene.h"

#include "LCSLaser.h"

namespace Ui {
class MainWindow;
}

/* ---------------------------------------------------------------------------------------------------------------- */
/* Main Window UI Controller Klasse                                                                                 */
/* ---------------------------------------------------------------------------------------------------------------- */

/**
 * @brief User Interface Controller (View Controller)
 *
 * Die MainWindow Klasse stellt die Schnittstelle zwischen dem User Interface und dem LCSLaser (Hardware-Controller)
 * her. Es werden die Events der Klasse Ui::MainWindow verarbeitet und auf Änderungen des LCSLaser eingegangen.
 */
class MainWindow : public QMainWindow, LCSSimulationInterface
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow * ui;    /**< User Interface (View) */

public:

    // Siehe LCSSimulationInterface in LCLaser.h
    void drawLine(LCSPoint from, LCSPoint to);      // Linie Zeichnen
    void laserUpdate();                             // Änderungen des Lasers verarbeiten
    bool proceedExecution();                        // Ausführungsindikator
    void finishedExecution();                       // Benachrichtigung über Ende der Befehlsausführung

    /**
     *  Setter & Getter für die Zeichenverzögerung
     */
    double drawAnimationTime();
    void setDrawAnimationTime(double timeInSeconds);

    /**
     *  Setter und Getter für die Befehlsverzögerung
     */
    double stepAnimationTime();
    void setStepAnimationTime(double timeInSeconds);

private slots:

    /*  Private Slots
     *
     *  Die folgenden Methoden werden durch die UserInterface Elemente aufgerufen.
     */

    void openButtonAction();            // Datei Öffnen Dialog
    void saveButtonAction();            // Datei Speichern Dialog

    void codeChangedAction();           // Änderungen am Steuercode
    void codeCursorChangedAction();     // Cursoränderung im Code Editor (für Zeilenhervorhebung)

    void runAutomaticAction();          // Befehle ausführen
    void stopAutomaticAction();         // Befehlsausführung stoppen

    void stepDelaySpinnerAction();      // Befehlsverzögerung
    void drawDelaySpinnerAction();      // Zeichenverzögerung

    void gridSizeSpinnerAction();       // Grid Abstand

private:
    LCSSyntaxHighlighter * _syntaxHighlighter;  /**< Syntaxerkennung        */

    double                 _drawAnimationTime;  /**< Animationszeit Draw    */
    double                 _stepAnimationTime;  /**< Animationszeit Steps   */
    LCSGridGraphicScene  * _graphicsScene;      /**< GraphicScene           */

    LCSLaser               _laser;              /**< Laser Controller       */

    bool                   _proceedExec;        /**< Ausführungsindikator   */
};

#endif // MAINWINDOW_H
