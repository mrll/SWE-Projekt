//
// Created by Matthias Röll, Marc Wüst
//

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
 * @brief Abstrakte Klasse um Methoden eines View Controllers vorzugeben
 *
 * Die Methoden werden von der Laserklasse in der Methode runInstructions benötigt, sofern
 * eine graphische Ausgabe erfolgen soll.
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
     * Wird gesendet sobald sich Werte des Lasers ändern.
     */
    virtual void laserUpdate() = 0;
    /**
     * @brief proceedExecution
     *
     * Zeigt an ob die Ausführung der Befehle weiterlaufen soll.
     *
     * @return Betriebsindikator
     */
    virtual bool proceedExecution() = 0;
    /**
     * @brief finishedExecution
     *
     * Benachrichtigung über das Ende einer Befehlsausführung
     */
    virtual void finishedExecution() = 0;
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
    class LCSEngineState *          _engineState;           /**< Motorenzustand     */
    class LCSLaserState  *          _laserState;            /**< Laserzustand       */

    LCSPoint                        _actualPosition;        /**< Akt. Position      */
    LCSPoint                        _desiredPosition;       /**< Neue Position      */

    LCSParser                       _parser;                /**< Parser             */
    std::vector<LCSParserCommand>   _commands;              /**< Befehle            */
    std::vector<LCSParserError>     _errors;                /**< Code Fehler        */

    int                             _currentCommandIndex;   /**< Befehlsnummer akt. */
    LCSPoint                        _codeGridSize;          /**< Größe in Punkten   */
public:
    LCSLaser();

    // Engine-State Setter und Bewegungsindikator
    void setEngineState(LCSEngineState * state);
    bool isMoving();

    // Engine-State Methoden
    void move(LCSPoint destination);
    void halt();

    // Laser-State Setter und Zustandsindikator
    void setLaserState(LCSLaserState * state);
    bool isLaserOn();

    // Laser-State Methoden
    void on();
    void off();

    // Setter Getter Positionen
    LCSPoint actualPosition();
    void setActualPosition(LCSPoint position);
    void setActualPosition(double x, double y);

    LCSPoint desiredPosition();
    void setDesiredPosition(LCSPoint destination);
    void setDesiredPosition(double x, double y);

    /**
     * @brief parseInstructionCode
     *
     * Gibt den Code an den Parser weiter und aktualisiert die
     * internen Variablen zum Speichern der Befehle, Fehler usw...
     *
     * @param code Code zum Übersetzen
     *
     * @return Fehler vorhanden
     */
    bool parseInstructionCode(std::string code);

    // Getter Parserinstruktionen
    std::vector<LCSParserCommand> commands();
    std::vector<LCSParserError> errors();

    /**
     * @brief runInstructions
     *
     * @param relative  Verarbeitet die Befehlswerte relativ wenn true
     * @param interface View Controller Klasse (Akzeptiert nullptr)
     *
     * @return false falls Fehler vorhanden sind
     */
    bool runInstructions(bool relative, LCSSimulationInterface * interface);

    // Sonstige Getter
    LCSPoint codeGridSize();
    LCSParserCommand currentCommand();
    int currentCommandIndex();
protected:

};

#endif // LCSLASER_H
