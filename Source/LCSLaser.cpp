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
    this->_engineState = new HALT(this);
    this->_laserState  = new OFF();

    this->_actualPosition  = zeroPoint();
    this->_desiredPosition = zeroPoint();

    this->_codeGridSize    = zeroPoint();
    this->_currentCommand  = LCSParserCommand();

    _commands.clear();
    _errors.clear();
}

/* ======================= */
/* Engine State            */
/* ======================= */

void LCSLaser::setEngineState(LCSEngineState * state) {
    this->_engineState = state;
}
bool LCSLaser::isMoving() {
    return this->_engineState->moving();
}

void LCSLaser::move(LCSPoint destination) {
    this->_engineState->move(this, destination);
}
void LCSLaser::halt() {
    this->_engineState->halt(this);
}

/* ======================= */
/* Laser State             */
/* ======================= */

void LCSLaser::setLaserState(LCSLaserState * state) {
    this->_laserState = state;
}
bool LCSLaser::isLaserOn() {
    return this->_laserState->isOn();
}

void LCSLaser::on() {
    this->_laserState->on(this);
}
void LCSLaser::off() {
    this->_laserState->off(this);
}

/* ======================= */
/* Aktuelle Position       */
/* ======================= */

void LCSLaser::setActualPosition(LCSPoint position) {
    this->_actualPosition = position;
}

void LCSLaser::setActualPosition(double x, double y) {
    this->_actualPosition.x = x;
    this->_actualPosition.y = y;
}

LCSPoint LCSLaser::actualPosition() {
    return this->_actualPosition;
}

/* ======================= */
/* Gewünschte Position     */
/* ======================= */

void LCSLaser::setDesiredPosition(LCSPoint position) {
    this->_desiredPosition = position;
}

void LCSLaser::setDesiredPosition(double x, double y) {
    this->_desiredPosition.x = x;
    this->_desiredPosition.y = y;
}

LCSPoint LCSLaser::desiredPosition() {
    return this->_desiredPosition;
}

/* ======================= */
/* Befehlsparsing          */
/* ======================= */

bool LCSLaser::parseInstructionCode(std::string code) {
    // Löschen alter Befehle und Fehler
    this->_errors.clear();
    this->_commands.clear();

    // Code Parsen
    this->_parser.parse(code, &(this->_commands), &(this->_errors));

    // Auslesen der Größe des zu zeichnenden Bildes
    int minX = 0, maxX = 0, minY = 0, maxY = 0;
    for (LCSParserCommand command : this->_commands) {
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
    this->_codeGridSize.x = (maxX - minX);
    this->_codeGridSize.y = (maxY - minY);

    // Ok wenn keine Fehler
    return this->_errors.size() == 0;
}

std::vector<LCSParserCommand> LCSLaser::commands() {
    return this->_commands;
}

std::vector<LCSParserError> LCSLaser::errors() {
    return this->_errors;
}

LCSPoint LCSLaser::codeGridSize() {
    return this->_codeGridSize;
}

LCSParserCommand LCSLaser::currentCommand() {
    return this->_currentCommand;
}

/* ======================= */
/* Befehle ausführen       */
/* ======================= */

bool LCSLaser::runInstructions(bool relative, LCSSimulationInterface * interface) {
    // Ausführung bei Fehlern verhindern
    if (this->_errors.size() > 0) {
        return false;
    } else {
        // Positionen des Lasers zurücksetzen
        this->_actualPosition = zeroPoint();
        this->_desiredPosition = zeroPoint();
        interface->laserUpdate();

        // Durch Befehle iterieren und ausführen
        for (LCSParserCommand command : this->_commands) {
            this->_currentCommand = command;
            switch (command.command) {
                case LCSCmdEngine: {
                    LCSPoint p;
                    if (relative) {
                        // Relative Werte berechnen
                        p = newPoint(this->_actualPosition.x + command.parameter[0],
                                     this->_actualPosition.y + command.parameter[1]);
                    } else {
                        // Absolute Werte nur setzen
                        p = newPoint(command.parameter[0], command.parameter[1]);
                    }
                    this->move(p);
                    interface->laserUpdate();
                    if (interface != nullptr && this->isLaserOn()) {
                        // Wenn eine View gegeben und der Laser an ist ist zeichnen
                        interface->drawLine(this->_actualPosition, p);
                    }
                    this->halt();
                    break;
                }
                case LCSCmdLaser: {
                    // Laser an/aus schalten
                    if (command.parameter[0] == 0) {
                        this->halt();
                        this->off();
                    } else {
                        this->halt();
                        this->on();
                    }
                    break;
                }
                default: {
                    std::cout << "Unbekannter Befehl! Bitte die Funktion: " << std::endl;
                    std::cout << "\t'bool LCSLaser::runInstructions(...)'" << std::endl;
                    std::cout << "in einer Subklasse überschreiben, um neue Befehle zu verarbeiten." << std::endl;
                    break;
                }
            }
            if (interface != nullptr) {
                // Update event senden, da Werte geändert wurden
                interface->laserUpdate();
                // Auf weitere Ausführung testen
                if (!interface->proceedExecution()) {
                    this->off();
                    break;
                }
            }
        }

        this->halt();
        this->_currentCommand = LCSParserCommand();
        if (interface != nullptr) {
            // Update event senden, da Werte geändert wurden
            interface->laserUpdate();
            // Ausführung der Befehle wurde beendet
            interface->finishedExecution();
        }
        return true;
    }
}
