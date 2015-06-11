//
// Created by Matthias Röll on 10.05.15.
//

#ifndef SWE_PROJEKT_LCCONTROLLER_H
#define SWE_PROJEKT_LCCONTROLLER_H

#include "../Model/LCParser.h"
#include "../Model/LCLaser.h"
#include "../Model/LCState.h"

class LCController {
public:
    LCController();
    ~LCController();

    // Getter
    LCLaser getLaser();

    QVector<LCParserCommand>    getCommands();
    QVector<LCParserError>      getErrors();

    QPoint                      getCodeDrawSize();

    // Code
    bool                        updateCode(QString code);

private:
    QVector<LCParserCommand>    _commands;
    QVector<LCParserError>      _errors;

    LCParser                    _parser;
    LCLaser                     _laser;
};


#endif //SWE_PROJEKT_LCCONTROLLER_H
