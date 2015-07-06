#ifndef LCSLASER_H
#define LCSLASER_H

#include "LCSParser.h"

/* ---------------------------------------------------------------------------------------------------------------- */
/* Koordinaten Typ Deklaration                                                                                      */
/* ---------------------------------------------------------------------------------------------------------------- */

typedef struct {
    double x;
    double y;
} LCSPoint;

/**
 * @brief zeroPoint
 *
 * @return Nullpunkt
 */
LCSPoint zeroPoint();
/**
 * @brief newPoint
 *
 * @param x X Koordinate
 * @param y Y Koordinate
 *
 * @return Punkt mit den Koordinaten (x, y)
 */
LCSPoint newPoint(int x, int y);

/* ---------------------------------------------------------------------------------------------------------------- */
/* Simulations Interface                                                                                            */
/* ---------------------------------------------------------------------------------------------------------------- */

/**
 * Abstrakte Klasse um Methoden eines View Controllers vorzugeben
 */
class LCSSimulationInterface
{
public:
    /**
     * @brief drawLine
     *
     * Methode zum Zeichnen einer Linie.
     *
     * @param from  Anfangspunkt der Linie
     * @param to    Endpunkt der Linie
     */
    virtual void drawLine(LCSPoint from, LCSPoint to) = 0;
    /**
     * @brief laserUpdate
     *
     * Wird gesendet sobeld sich Werte des Lasers ändern.
     */
    virtual void laserUpdate() = 0;
};

/* ---------------------------------------------------------------------------------------------------------------- */
/* Laser Klasse                                                                                                     */
/* ---------------------------------------------------------------------------------------------------------------- */

/**
 * @brief Laser Controller Klasse
 *
 * Stellt die Schnittstelle zwischen dem Parser, der View und der Hardware (States) her.
 */
class LCSLaser
{
private:
    class LCSEngineState *          _engineState;       /**< Motorenzustand     */
    class LCSLaserState  *          _laserState;        /**< Laserzustand       */

    LCSPoint                        _actualPosition;    /**< Akt. Position      */
    LCSPoint                        _desiredPosition;   /**< Neue Position      */

    LCSParser                       _parser;            /**< Parser             */
    std::vector<LCSParserCommand>   _commands;          /**< Befehle            */
    std::vector<LCSParserError>     _errors;            /**< Code Fehler        */

    LCSParserCommand                _currentCommand;    /**< Aktueller Befehl   */
    LCSPoint                        _codeGridSize;      /**< Größe in Punkten   */
public:
    /**
     * @brief LCSLaser Konstruktor
     */
    LCSLaser();

    /**
     * @brief setEngineState
     * @param state
     */
    void setEngineState(LCSEngineState * state);
    /**
     * @brief isMoving
     * @return
     */
    bool isMoving();

    /**
     * @brief move
     * @param destination
     */
    void move(LCSPoint destination);
    /**
     * @brief halt
     */
    void halt();

    /**
     * @brief setLaserState
     * @param state
     */
    void setLaserState(LCSLaserState * state);
    /**
     * @brief isLaserOn
     * @return
     */
    bool isLaserOn();

    /**
     * @brief on
     */
    void on();
    /**
     * @brief off
     */
    void off();

    /**
     * @brief actualPosition
     * @return
     */
    LCSPoint actualPosition();
    /**
     * @brief setActualPosition
     * @param position
     */
    void setActualPosition(LCSPoint position);
    void setActualPosition(double x, double y);

    /**
     * @brief desiredPosition
     * @return
     */
    LCSPoint desiredPosition();
    /**
     * @brief setDesiredPosition
     * @param destination
     */
    void setDesiredPosition(LCSPoint destination);
    void setDesiredPosition(double x, double y);

    /**
     * @brief parseInstructionCode
     * @param code
     * @return
     */
    bool parseInstructionCode(std::string code);

    /**
     * @brief commands
     * @return
     */
    std::vector<LCSParserCommand> commands();
    /**
     * @brief errors
     * @return
     */
    std::vector<LCSParserError> errors();

    /**
     * @brief runInstructions
     * @param relative
     * @param interface
     * @return
     */
    bool runInstructions(bool relative, LCSSimulationInterface * interface);

    /**
     * @brief codeGridSize
     * @return
     */
    LCSPoint codeGridSize();
    /**
     * @brief currentCommand
     * @return
     */
    LCSParserCommand currentCommand();
protected:

};

#endif // LCSLASER_H
