//
// Created by Matthias Röll, Marc Wüst on 09.05.15.
//

#ifndef SWE_PROJEKT_LASER_H
#define SWE_PROJEKT_LASER_H

#include <QTCore/QPoint>

class LCLaser {
    class LCPowerState  * _currentPowerState;
    class LCEngineState * _currentEngineState;

public:
#pragma mark De-/Konstruktor
    LCLaser();
    LCLaser(QPoint position);
    ~LCLaser();

#pragma mark Power State
    void setPower(LCPowerState * powerState);
    bool isOn();

    void on();
    void off();

#pragma mark Engine State
    void setEngine(LCEngineState * engineState);
    bool isMoving();

    void move();
    void halt();

#pragma mark Position
    QPoint actualPosition();
    void setActualPosition(QPoint position);

protected:
    QPoint *_actualPosition;
};

#endif //SWE_PROJEKT_LASER_H
