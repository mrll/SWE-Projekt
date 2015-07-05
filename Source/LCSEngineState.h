#ifndef LCSENGINESTATE_H
#define LCSENGINESTATE_H

#include "LCSLaser.h"

/**
 * Basisklasse des Zustands der Bewegungsmotoren
 */
class LCSEngineState
{
public:
    virtual void move(LCSLaser * laser, LCSPoint destination);
    virtual void halt(LCSLaser * laser);
    virtual bool moving();
};

/**
 * Move-Zustandsklasse
 */
class MOVE : public LCSEngineState
{
public:
    MOVE(LCSLaser * laser);
    void halt(LCSLaser * laser);
    bool moving();
};

/**
 * Halt-Zustandsklasse
 */
class HALT : public LCSEngineState
{
public:
    HALT(LCSLaser * laser);
    void move(LCSLaser * laser, LCSPoint destination);
};

#endif // LCSENGINESTATE_H
