//
// Created by Matthias Röll, Marc Wüst on 09.05.15.
//

#ifndef SWE_PROJEKT_LASERSTATE_H
#define SWE_PROJEKT_LASERSTATE_H

#include "LCLaser.h"

#pragma mark Power State

class LCPowerState {
public:
    virtual void on(LCLaser * laser);
    virtual void off(LCLaser * laser);
};

class ON: public LCPowerState {
public:
    ON();
    ~ON();

    void off(LCLaser *laser);
};

class OFF: public LCPowerState {
public:
    OFF();
    ~OFF();

    void on(LCLaser *laser);
};

#pragma mark Engine State

class LCEngineState {
public:
    virtual void move(LCLaser * laser);
    virtual void halt(LCLaser * laser);
};

class MOVE: public LCEngineState {
public:
    MOVE();
    ~MOVE();

    void halt(LCLaser *laser);
};

class HALT: public LCEngineState {
public:
    HALT();
    ~HALT();

    void move(LCLaser *laser);
};

#endif //SWE_PROJEKT_LASERSTATE_H
