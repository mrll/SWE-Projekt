//
// Created by Matthias Röll, Marc Wüst on 09.05.15.
//

#include "LCParser.h"

#pragma mark RegEx

const QRegExp * LCParser::moveExp      = new QRegExp("^\\s?(MOVE)\\s+(\\d){1,4}\\s*,(\\s)*(\\d){1,4}(?:\\s*\\#+.*|\\s*)$",
                                                     Qt::CaseSensitive,
                                                     QRegExp::RegExp);
const QRegExp * LCParser::powerExp     = new QRegExp("^\\s?(LASER)\\s+(ON|OFF)(?:\\s*\\#+.*|\\s*)$",
                                                     Qt::CaseSensitive,
                                                     QRegExp::RegExp);
const QRegExp * LCParser::commentExp   = new QRegExp("\\s?\\#+.*$",
                                                     Qt::CaseSensitive,
                                                     QRegExp::RegExp);

#pragma mark LCParserError

LCParserError::LCParserError(QString string, int line, LCErrorCode code) {
    this->string = string;
    this->line = line;
    this->code = code;
}
LCParserError::LCParserError() {
    this->string = "";
    this->line = -1;
    this->code = LCErrNone;
}

#pragma mark LCParserCommand

LCParserCommand::LCParserCommand(LCCommandCode command, int parameter1, int parameter2) {
    this->command = command;
    this->parameter1 = parameter1;
    this->parameter2 = parameter2;
}
LCParserCommand::LCParserCommand() {
    this->command = LCUnknownCommand;
    this->parameter1 = 0;
    this->parameter2 = 0;
}

#pragma mark LCParser

LCParser::LCParser() {
    this->validators = new QVector<validatorFunction>();

    this->validators->append(LCParser::moveExpValidator);
    this->validators->append(LCParser::powerExpValidator);
}

bool LCParser::parse(QString code, QVector<LCParserCommand> * commands, QVector<LCParserError> * errors) {
    if (commands == NULL || errors == NULL) {
        return false;
    }

    QStringList codeLines = code.split("\n", QString::SplitBehavior::KeepEmptyParts);   // Generate line list
    QStringList::iterator it = codeLines.begin();

    while (it != codeLines.end()) {
        if (it->isEmpty() || commentExp->exactMatch(it->toUpper())) {          // Check if empty or comment
            // Do nothing
        } else {
            LCParserCommand command;

            for (int i = 0; i < validators->count(); ++i) {
                if (validators->at(i)(*it, &command)) {
                    commands->append(command);
                    break;
                }
            }

            if (command.command == LCUnknownCommand) {
                errors->append(findLineError(*it, it - codeLines.begin()));
            }
        }

        ++it;
    }

    return errors->isEmpty();   // No errors if isEmpty
}

LCParserError LCParser::findLineError(QString string, int line) {
    // TODO: Implement error detection
    return LCParserError(string, line, LCErrNone);
}

bool LCParser::moveExpValidator(QString string, LCParserCommand * command) {
    if (command != NULL && LCParser::moveExp->exactMatch(string.toUpper())) {
        QStringList list = LCParser::moveExp->capturedTexts();
        // List contains [0] full string, [1] MOVE, [2] parameter 1, [3] parameter 2
        command->command = LCMoveCommand;
        command->parameter1 = list[2].toInt();
        command->parameter2 = list[3].toInt();
        return true;
    }
    return false;
}

bool LCParser::powerExpValidator(QString string, LCParserCommand * command) {
    if (command != NULL && LCParser::powerExp->exactMatch(string.toUpper())) {
        QStringList list = LCParser::powerExp->capturedTexts();
        // List contains [0] full string, [1] LASER, [2] parameter 1
        command->command = LCPowerCommand;
        command->parameter1 = list[2].toInt();
        command->parameter2 = 0;
        return true;
    }
    return false;
}
