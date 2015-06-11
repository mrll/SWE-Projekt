//
// Created by Matthias Röll, Marc Wüst on 09.05.15.
//

#include <iostream>
#include "LCState.h"

// TODO: Platzhalter cout's durch Aktionen ersetzen

#pragma mark Laser State

void LCPowerState::on(LCLaser *laser) {
    std::cout << "   already ON\n";
}
void LCPowerState::off(LCLaser *laser) {
    std::cout << "   already OFF\n";
}

ON::ON() {
    std::cout << "   ON-ctor ";
}
ON::~ON() {
    std::cout << "   ON-dtor ";
}
void ON::off(LCLaser *laser) {
    std::cout << "   going from ON to OFF";
    laser->setPower(new OFF());
}

OFF::OFF() {
    std::cout << "   OFF-ctor ";
}
OFF::~OFF() {
    std::cout << "   OFF-dtor ";
}
void OFF::on(LCLaser *laser) {
    std::cout << "   going from OFF to ON";
    laser->setPower(new ON());
}

#pragma mark Movement State

void LCEngineState::move(LCLaser *laser) {
    std::cout << "   already MOVEing\n";
}
void LCEngineState::halt(LCLaser *laser) {
    std::cout << "   already HALTed\n";
}

MOVE::MOVE() {
    std::cout << "   MOVE-ctor ";
}
MOVE::~MOVE() {
    std::cout << "   MOVE-dtor ";
}
void MOVE::halt(LCLaser *laser) {
    std::cout << "   going from MOVE to HALT";
    laser->setEngine(new HALT());
}

HALT::HALT() {
    std::cout << "   HALT-ctor ";
}
HALT::~HALT() {
    std::cout << "   HALT-dtor ";
}
void HALT::move(LCLaser *laser) {
    std::cout << "   going from HALT to MOVE";
    laser->setEngine(new MOVE());
}
