//
// Created by Matthias Röll on 10.05.15.
//

#ifndef SWE_PROJEKT_LASERCUTTERUI_H
#define SWE_PROJEKT_LASERCUTTERUI_H

#include "LCUI_Base.h"
#include "LCSyntaxHighlighter.h"

#pragma mark Lasercutter UI Class
class LCUserInterface : public QMainWindow, public Ui::MainWindow{
    Q_OBJECT

public:

#pragma mark De-/Konstruktor

    LCUserInterface(QMainWindow *parent = 0);
    ~LCUserInterface();

#pragma mark Simulation Drawing

    void drawLine(QPoint from, QPoint to);

    float drawAnimationTime();
    void setDrawAnimationTime(float timeInSeconds);

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
    LCSyntaxHighlighter * syntaxHighlighter;

    float               _drawAnimationTime;

    QGraphicsScene      * _graphicsScene;
    QTimer              * _timer;
};


#endif //SWE_PROJEKT_LASERCUTTERUI_H
