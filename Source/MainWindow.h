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

class MainWindow : public QMainWindow, LCSSimulationInterface
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    /**
     * @brief ui
     */
    Ui::MainWindow * ui;

public:
    /**
     * @brief drawLine
     * @param from
     * @param to
     */
    void drawLine(LCSPoint from, LCSPoint to);
    /**
     * @brief laserUpdate
     */
    void laserUpdate();
    /**
     * @brief proceedExecution
     * @return
     */
    bool proceedExecution();

    /**
     * @brief drawAnimationTime
     * @return
     */
    int drawAnimationTime();
    /**
     * @brief setDrawAnimationTime
     * @param timeInSeconds
     */
    void setDrawAnimationTime(int timeInSeconds);

    /**
     * @brief stepAnimationTime
     * @return
     */
    int stepAnimationTime();
    /**
     * @brief setStepAnimationTime
     * @param timeInSeconds
     */
    void setStepAnimationTime(int timeInSeconds);

private slots:
    /**
     * @brief openButtonAction
     */
    void openButtonAction();
    /**
     * @brief saveButtonAction
     */
    void saveButtonAction();

    /**
     * @brief codeChangedAction
     */
    void codeChangedAction();
    /**
     * @brief codeCursorChangedAction
     */
    void codeCursorChangedAction();

    /**
     * @brief runAutomaticAction
     */
    void runAutomaticAction();
    /**
     * @brief stopAutomaticAction
     */
    void stopAutomaticAction();

private:
    LCSSyntaxHighlighter * _syntaxHighlighter;  /**< Syntaxerkennung        */

    int                    _drawAnimationTime;  /**< Animationszeit Draw    */
    int                    _stepAnimationTime;  /**< Animationszeit Steps   */
    LCSGridGraphicScene  * _graphicsScene;      /**< GraphicScene           */

    LCSLaser               _laser;              /**< Laser Controller       */

    bool                   _proceedExec;        /**< Ausführungsindikator   */
};

#endif // MAINWINDOW_H
