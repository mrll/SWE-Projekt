//
// Created by Matthias Röll, Marc Wüst
//

#ifndef LCSLASERSTATE_H
#define LCSLASERSTATE_H

#include "LCSLaser.h"

/* ---------------------------------------------------------------------------------------------------------------- */
/* Laser State Basisklasse                                                                                          */
/* ---------------------------------------------------------------------------------------------------------------- */

/**
 * Basisklasse des Zustands der Laseransteuerung
 */
class LCSLaserState
{
public:
    /**
     * Senden der Hardwarebefehle zum Anschalten des Lasers
     *
     * @param LCSLaser * laser       Laser für die Ausführung
     */
    virtual void on(LCSLaser * laser);
    /**
     * Senden der Hardwarebefehle zum Ausschalten des Lasers
     *
     * @param LCSLaser * laser       Laser für die Ausführung
     */
    virtual void off(LCSLaser * laser);
    /**
     * Zustandsindikator
     *
     * @return true wenn in An, sonst false
     */
    virtual bool isOn();
};

/* ---------------------------------------------------------------------------------------------------------------- */
/* ON State                                                                                                         */
/* ---------------------------------------------------------------------------------------------------------------- */

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

/* ---------------------------------------------------------------------------------------------------------------- */
/* OFF State                                                                                                        */
/* ---------------------------------------------------------------------------------------------------------------- */

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
