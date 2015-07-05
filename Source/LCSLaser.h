#ifndef LCSLASER_H
#define LCSLASER_H

#include "LCSParser.h"

typedef struct {
    double x;
    double y;
} LCSPoint;

LCSPoint zeroPoint();
LCSPoint newPoint(int x, int y);

class LCSSimulationInterface
{
public:
    virtual void drawLine(LCSPoint from, LCSPoint to) = 0;
    virtual void laserUpdate() = 0;
};

class LCSLaser
{
private:
    class LCSEngineState *          _engineState;
    class LCSLaserState  *          _laserState;

    LCSPoint                        _actualPosition;
    LCSPoint                        _desiredPosition;

    LCSParser                       _parser;
    std::vector<LCSParserCommand>   _commands;
    std::vector<LCSParserError>     _errors;

    LCSParserCommand                _currentCommand;
    LCSPoint                        _codeGridSize;
public:
    LCSLaser();

    void setEngineState(LCSEngineState * state);
    bool isMoving();

    void move(LCSPoint destination);
    void halt();

    void setLaserState(LCSLaserState * state);
    bool isLaserOn();

    void on();
    void off();

    LCSPoint actualPosition();
    void setActualPosition(LCSPoint position);
    void setActualPosition(double x, double y);

    LCSPoint desiredPosition();
    void setDesiredPosition(LCSPoint destination);
    void setDesiredPosition(double x, double y);

    bool parseInstructionCode(std::string code);

    std::vector<LCSParserCommand> commands();
    std::vector<LCSParserError> errors();

    bool runInstructions(bool relative, LCSSimulationInterface * interface);

    LCSPoint codeGridSize();
    LCSParserCommand currentCommand();
protected:

};

#endif // LCSLASER_H
