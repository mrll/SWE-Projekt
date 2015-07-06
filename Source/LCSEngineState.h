#ifndef LCSENGINESTATE_H
#define LCSENGINESTATE_H

#include "LCSLaser.h"

/* ---------------------------------------------------------------------------------------------------------------- */
/* Engine State Basisklasse                                                                                         */
/* ---------------------------------------------------------------------------------------------------------------- */

/**
 * Basisklasse des Zustands der Bewegungsmotoren
 */
class LCSEngineState
{
public:
    /**
     * Senden der Hardwarebefehle für die Bewegung
     *
     * @param LCSLaser * laser       Laser für die Ausführung
     * @param LCSPoint * destination Zielkoordinaten
     */
    virtual void move(LCSLaser * laser, LCSPoint destination);
    /**
     * Senden der Hardwarebefehle zum Beenden einer Bewegung
     *
     * @param LCSLaser * laser       Laser für die Ausführung
     */
    virtual void halt(LCSLaser * laser);
    /**
     * Bewegungsindikator
     *
     * @return true wenn in Bewegung, sonst false
     */
    virtual bool moving();
};

/* ---------------------------------------------------------------------------------------------------------------- */
/* Move State                                                                                                       */
/* ---------------------------------------------------------------------------------------------------------------- */

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

/* ---------------------------------------------------------------------------------------------------------------- */
/* Halt State                                                                                                       */
/* ---------------------------------------------------------------------------------------------------------------- */

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
