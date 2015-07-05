#ifndef LCSLASERSTATE_H
#define LCSLASERSTATE_H

#include "LCSLaser.h"

/**
 * Basisklasse des Zustands der Laseransteuerung
 */
class LCSLaserState
{
public:
    virtual void on(LCSLaser * laser);
    virtual void off(LCSLaser * laser);
    virtual bool isOn();
};

/**
 * ON-Zustandsklasse
 */
class ON : public LCSLaserState
{
public:
    ON();
    void off(LCSLaser * laser);
    bool isOn();
};

/**
 * OFF-Zustandsklasse
 */
class OFF : public LCSLaserState
{
public:
    OFF();
    void on(LCSLaser * laser);
};

#endif // LCSLASERSTATE_H
