#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "LCSSyntaxHighlighter.h"
#include "LCSGridGraphicScene.h"

#include "LCSLaser.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, LCSSimulationInterface
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow * ui;

public:
    void drawLine(LCSPoint from, LCSPoint to);
    void laserUpdate();

    int drawAnimationTime();
    void setDrawAnimationTime(int timeInSeconds);

private slots:
    void openButtonAction();
    void saveButtonAction();

    void codeChangedAction();
    void codeCursorChangedAction();

    void runAutomaticAction();

private:
    LCSSyntaxHighlighter * _syntaxHighlighter;

    int                    _drawAnimationTime;
    LCSGridGraphicScene  * _graphicsScene;

    LCSLaser               _laser;
};

#endif // MAINWINDOW_H
