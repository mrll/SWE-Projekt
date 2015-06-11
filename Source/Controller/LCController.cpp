//
// Created by Matthias Röll on 10.05.15.
//

#include"LCController.h"

LCController::LCController() {
    _commands   = QVector<LCParserCommand>();
    _errors     = QVector<LCParserError>();

    _parser     = LCParser();
    _laser      = LCLaser();
}
LCController::~LCController() {

}

// Getter
LCLaser LCController::getLaser() {
    return _laser;
}

QVector<LCParserCommand> LCController::getCommands() {
    return _commands;
}
QVector<LCParserError> LCController::getErrors() {
    return _errors;
}

QPoint LCController::getCodeDrawSize() {
    QPoint minPos = QPoint(), maxPos = QPoint();

    for (int j = 0; j < _commands.count(); ++j) {
        if (_commands.at(j).command == LCMoveCommand) {
            if (_commands.at(j).parameter[0] < minPos.x()) {
                minPos.setX(_commands.at(j).parameter[0]);
            } else if (_commands.at(j).parameter[0] > maxPos.x()) {
                maxPos.setX(_commands.at(j).parameter[0]);
            }

            if (_commands.at(j).parameter[1] < minPos.y()) {
                minPos.setY(_commands.at(j).parameter[1]);
            } else if (_commands.at(j).parameter[1] > maxPos.y()) {
                maxPos.setY(_commands.at(j).parameter[1]);
            }
        }
    }

    return maxPos - minPos;
}

// Code
bool LCController::updateCode(QString code) {
    _commands.clear();
    _errors.clear();
    return _parser.parse(code, &_commands, &_errors);
}
