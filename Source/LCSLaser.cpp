//
// Created by Matthias Röll, Marc Wüst
//

#include "LCSLaser.h"

#include "LCSEngineState.h"
#include "LCSLaserState.h"

#include <typeinfo>
#include <iostream>

/* ---------------------------------------------------------------------------------------------------------------- */
/* Point Typ (Hilfsfunktionen)                                                                                      */
/* ---------------------------------------------------------------------------------------------------------------- */

LCSPoint zeroPoint() {
    return {0.0, 0.0};
}

LCSPoint newPoint(int x, int y) {
    LCSPoint p;
    p.x = x;
    p.y = y;
    return p;
}

/* ---------------------------------------------------------------------------------------------------------------- */
/* Laser Klasse                                                                                                     */
/* ---------------------------------------------------------------------------------------------------------------- */

/* ======================= */
/* Konstruktor             */
/* ======================= */

LCSLaser::LCSLaser() {
    // Defaultwerte setzen
    _engineState = new HALT(this);
    _laserState  = new OFF();

    _actualPosition  = zeroPoint();
    _desiredPosition = zeroPoint();

    _codeGridSize           = zeroPoint();
    _currentCommandIndex    = -1;

    _commands.clear();
    _errors.clear();
}

/* ======================= */
/* Engine State            */
/* ======================= */

void LCSLaser::setEngineState(LCSEngineState * state) {
    _engineState = state;
}
bool LCSLaser::isMoving() {
    return _engineState->moving();
}

void LCSLaser::move(LCSPoint destination) {
    _engineState->move(this, destination);
}
void LCSLaser::halt() {
    _engineState->halt(this);
}

/* ======================= */
/* Laser State             */
/* ======================= */

void LCSLaser::setLaserState(LCSLaserState * state) {
    _laserState = state;
}
bool LCSLaser::isLaserOn() {
    return _laserState->isOn();
}

void LCSLaser::on() {
    _laserState->on(this);
}
void LCSLaser::off() {
    _laserState->off(this);
}

/* ======================= */
/* Aktuelle Position       */
/* ======================= */

void LCSLaser::setActualPosition(LCSPoint position) {
    _actualPosition = position;
}

void LCSLaser::setActualPosition(double x, double y) {
    _actualPosition.x = x;
    _actualPosition.y = y;
}

LCSPoint LCSLaser::actualPosition() {
    return _actualPosition;
}

/* ======================= */
/* Gewünschte Position     */
/* ======================= */

void LCSLaser::setDesiredPosition(LCSPoint position) {
    _desiredPosition = position;
}

void LCSLaser::setDesiredPosition(double x, double y) {
    _desiredPosition.x = x;
    _desiredPosition.y = y;
}

LCSPoint LCSLaser::desiredPosition() {
    return _desiredPosition;
}

/* ======================= */
/* Befehlsparsing          */
/* ======================= */

bool LCSLaser::parseInstructionCode(std::string code) {
    // Löschen alter Befehle und Fehler
    _errors.clear();
    _commands.clear();

    // Code Parsen
    _parser.parse(code, &_commands, &_errors);

    // Auslesen der Größe des zu zeichnenden Bildes
    int minX = 0, maxX = 0, minY = 0, maxY = 0;

    for (LCSParserCommand command : _commands) {
        if (command.command == LCSCmdEngine) {
            if (command.parameter[0] < minX) {
                minX = command.parameter[0];
            }
            if (command.parameter[0] > maxX) {
                maxX = command.parameter[0];
            }
            if (command.parameter[1] < minY) {
                minY = command.parameter[1];
            }
            if (command.parameter[1] > maxY) {
                maxY = command.parameter[1];
            }
        }
    }
    _codeGridSize.x = (maxX - minX);
    _codeGridSize.y = (maxY - minY);

    // Ok wenn keine Fehler
    return _errors.size() == 0;
}

std::vector<LCSParserCommand> LCSLaser::commands() {
    return _commands;
}

std::vector<LCSParserError> LCSLaser::errors() {
    return _errors;
}

LCSPoint LCSLaser::codeGridSize() {
    return _codeGridSize;
}

LCSParserCommand LCSLaser::currentCommand() {
    if (_currentCommandIndex >= 0 && (size_t)_currentCommandIndex < _commands.size()) {
        return _commands.at(_currentCommandIndex);
    }
    return LCSParserCommand();
}

int LCSLaser::currentCommandIndex() {
    return _currentCommandIndex;
}

/* ======================= */
/* Befehle ausführen       */
/* ======================= */

bool LCSLaser::runInstructions(bool relative, LCSSimulationInterface * interface) {
    // Ausführung bei Fehlern verhindern
    if (_errors.size() > 0) {
        return false;
    } else {
        // Positionen des Lasers zurücksetzen
        _actualPosition = zeroPoint();
        _desiredPosition = zeroPoint();

        if (interface != nullptr) {
            interface->laserUpdate();
        }

        // Durch Befehle iterieren und ausführen (keine foreach da index gebraucht wird)
        for (int i = 0; (size_t)i < _commands.size(); i++) {
            // Aktuellen Befehlsindex setzen
            _currentCommandIndex = i;

            switch (_commands[i].command) {
                case LCSCmdEngine: {                    // MOVE Verarbeitung
                    LCSPoint p;

                    if (relative) {
                        // Relative Werte berechnen
                        p = newPoint(_actualPosition.x + _commands[i].parameter[0],
                                     _actualPosition.y + _commands[i].parameter[1]);
                    } else {
                        // Absolute Werte nur setzen
                        p = newPoint(_commands[i].parameter[0], _commands[i].parameter[1]);
                    }

                    // Hardware fahren
                    move(p);
                    // Simulation fahren
                    if (interface != nullptr) {
                        interface->laserUpdate();
                        if (isLaserOn()) {
                            // Wenn eine View gegeben und der Laser an ist ist zeichnen
                            interface->drawLine(_actualPosition, p);
                        }
                    }

                    halt();
                    break;
                }
                case LCSCmdLaser: {                     // LASER Verarbeitung
                    // Laser an/aus schalten
                    if (_commands[i].parameter[0] == 0) {
                        halt();
                        off();
                    } else {
                        halt();
                        on();
                    }
                    break;
                }
                default: {                              // UNKNOWN Verarbeitung

                    std::cout << "Unbekannter Befehl! Bitte die Funktion: " << std::endl;
                    std::cout << "\t'bool LCSLaser::runInstructions(...)'" << std::endl;
                    std::cout << "in einer Subklasse überschreiben, um neue Befehle zu verarbeiten." << std::endl;

                    break;
                }
            }

            // Update event senden, da Werte geändert wurden
            if (interface != nullptr) {
                interface->laserUpdate();
                // Auf weitere Ausführung testen
                if (!interface->proceedExecution()) {
                    off();
                    break;
                }
            }
        }

        halt();

        // Befehlsindex zurücksetzen
        _currentCommandIndex = -1;

        if (interface != nullptr) {
            // Update event senden, da Werte geändert wurden
            interface->laserUpdate();
            // Ausführung der Befehle wurde beendet
            interface->finishedExecution();
        }
        return true;
    }
}
