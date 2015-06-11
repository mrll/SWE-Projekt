//
// Created by Matthias Röll, Marc Wüst on 09.05.15.
//

#include "LCLaser.h"
#include "LCState.h"

#include <typeinfo>

#pragma mark De-/Konstruktor

LCLaser::LCLaser() {
    _currentPowerState = new OFF();
    _currentEngineState = new HALT();
    _actualPosition = new QPoint(0, 0);
}
LCLaser::LCLaser(QPoint position) {
    _currentPowerState = new OFF();
    _currentEngineState = new HALT();
    _actualPosition =  new QPoint(position.x(), position.y());
}
LCLaser::~LCLaser() {
}

#pragma mark Power State

void LCLaser::setPower(LCPowerState * powerState) {
    _currentPowerState = powerState;
}
bool LCLaser::isOn() {
    return typeid(_currentPowerState).name() == typeid(ON).name();
}

void LCLaser::on() {
    _currentPowerState->on(this);
}
void LCLaser::off() {
    _currentPowerState->off(this);
}

#pragma mark Engine State

void LCLaser::setEngine(LCEngineState * engineState) {
    _currentEngineState = engineState;
}
bool LCLaser::isMoving() {
    return typeid(_currentEngineState).name() == typeid(MOVE).name();
}

void LCLaser::move() {
    _currentEngineState->move(this);
}
void LCLaser::halt() {
    _currentEngineState->halt(this);
}

#pragma mark Position

QPoint LCLaser::actualPosition() {
    return *_actualPosition;
}
void LCLaser::setActualPosition(QPoint position) {
    _actualPosition->setX(position.x());
    _actualPosition->setY(position.y());
}
