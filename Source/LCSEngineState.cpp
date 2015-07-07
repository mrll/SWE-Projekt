//
// Created by Matthias Röll, Marc Wüst
//

#include "LCSEngineState.h"

/* ---------------------------------------------------------------------------------------------------------------- */
/* Basisklasse                                                                                                      */
/* ---------------------------------------------------------------------------------------------------------------- */

void LCSEngineState::move(LCSLaser *laser, LCSPoint destination) {
    // Neue Laserposition aktualisieren
    if (laser->desiredPosition().x != destination.x ||
        laser->desiredPosition().x != destination.x) {
        laser->setDesiredPosition(destination);
    }
}

void LCSEngineState::halt(LCSLaser *laser) {
    // Nichts zu tun da schon in Halt
}

bool LCSEngineState::moving() {
    return false;
}

/* ---------------------------------------------------------------------------------------------------------------- */
/* Move Klasse                                                                                                      */
/* ---------------------------------------------------------------------------------------------------------------- */

MOVE::MOVE(LCSLaser * laser) {
    // Hardwarebefehle schicken
}

void MOVE::halt(LCSLaser *laser) {
    laser->setActualPosition(laser->desiredPosition());
    laser->setEngineState(new HALT(laser));
}

bool MOVE::moving() {
    return true;
}

/* ---------------------------------------------------------------------------------------------------------------- */
/* Halt Klasse                                                                                                      */
/* ---------------------------------------------------------------------------------------------------------------- */

HALT::HALT(LCSLaser * laser) {
    // Hardwarebefehle schicken
}

void HALT::move(LCSLaser *laser, LCSPoint destination) {
    laser->setDesiredPosition(destination);
    laser->setEngineState(new MOVE(laser));
}
