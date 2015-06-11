//
// Created by Matthias Röll on 10.05.15.
//

#ifndef SWE_PROJEKT_LASERCUTTERUI_H
#define SWE_PROJEKT_LASERCUTTERUI_H

#include "LCUI_Base.h"
#include "LCSyntaxHighlighter.h"
#include "LCGridGraphicScene.h"

class LCController;
class LCGridGraphicScene;

#pragma mark Lasercutter UI Class
class LCUserInterface : public QMainWindow, public Ui::MainWindow{
    Q_OBJECT

public:

#pragma mark De-/Konstruktor

    LCUserInterface(QMainWindow *parent = 0);
    ~LCUserInterface();

#pragma mark Controller
    LCController * controller;

#pragma mark Simulation Drawing

    void drawLine(QPoint from, QPoint to);

    int drawAnimationTime();
    void setDrawAnimationTime(int timeInSeconds);

private slots:

#pragma mark Steuercode Tab Actions

    void openButtonAction();
    void saveButtonAction();

    void codeChangedAction();
    void codeCursorChangedAction();

#pragma mark Simulation Tab Actions

    void runAutomaticAction();

    void runManualAction();
    void toggleLaserAction();

private:

#pragma mark Private Member Variables & Methods
    LCSyntaxHighlighter * _syntaxHighlighter;

    int                   _drawAnimationTime;
    LCGridGraphicScene  * _graphicsScene;

    LCController        * _controller;
};


#endif //SWE_PROJEKT_LASERCUTTERUI_H
