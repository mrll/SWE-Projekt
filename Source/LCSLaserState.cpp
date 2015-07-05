#include "LCSLaserState.h"

/* ---------------------------------------------------------------------------------------------------------------- */
/* Basisklasse                                                                                                      */
/* ---------------------------------------------------------------------------------------------------------------- */

void LCSLaserState::on(LCSLaser *laser) {
    // Nichts zu tun da schon in on
}

void LCSLaserState::off(LCSLaser *laser) {
    // Nichts zu tun da schon in off
}

bool LCSLaserState::isOn() {
    return false;
}

/* ---------------------------------------------------------------------------------------------------------------- */
/* Move Klasse                                                                                                      */
/* ---------------------------------------------------------------------------------------------------------------- */

ON::ON() {
    // Hardwarebefehle schicken
}

void ON::off(LCSLaser *laser) {
    laser->setLaserState(new OFF());
}

bool ON::isOn() {
    return true;
}

/* ---------------------------------------------------------------------------------------------------------------- */
/* Halt Klasse                                                                                                      */
/* ---------------------------------------------------------------------------------------------------------------- */

OFF::OFF() {
    // Hardwarebefehle schicken
}

void OFF::on(LCSLaser *laser) {
    laser->setLaserState(new ON());
}
