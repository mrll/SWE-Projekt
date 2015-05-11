//
// Created by Matthias Röll, Marc Wüst on 09.05.15.
//

#include "LCParser.h"

#pragma mark RegEx
/* ---------------------------------------------------------------------------------------------------------------- */

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
/* ---------------------------------------------------------------------------------------------------------------- */

/* ==================== */
/* Konstruktoren        */
/* ==================== */

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
/* ---------------------------------------------------------------------------------------------------------------- */

/* ==================== */
/* Konstruktoren        */
/* ==================== */

LCParserCommand::LCParserCommand(LCCommandCode command, int * parameter, int parameterCount) {
    this->command           = command;
    this->parameter         = parameter;
    this->parameterCount    = parameterCount;
}
LCParserCommand::LCParserCommand() {
    this->command           = LCUnknownCommand;
    this->parameter         = (int *) malloc(sizeof(int) * 2);
    this->parameterCount    = 2;
}

#pragma mark LCParser
/* ---------------------------------------------------------------------------------------------------------------- */

/* ==================== */
/* Konstruktor          */
/* ==================== */

LCParser::LCParser() {
    this->validators = new QVector<validatorFunction>();

    this->validators->append(LCParser::moveExpValidator);
    this->validators->append(LCParser::powerExpValidator);

    // Weitere Validatoren können in vererbten Klassen hinzugefügt werden.
}

/* ==================== */
/* parse                */
/* ==================== */

bool LCParser::parse(QString code, QVector<LCParserCommand> * commands, QVector<LCParserError> * errors) {
    if (commands == NULL || errors == NULL) {
        return false;
    }

    // Der Code wird in Zeilen aufgespalten und iteriert
    QStringList codeLines = code.split("\n", QString::SplitBehavior::KeepEmptyParts);
    QStringList::iterator it = codeLines.begin();

    while (it != codeLines.end()) {
        if (it->isEmpty() || commentExp->exactMatch(it->toUpper())) {
            // Bei leeren Zeilen oder Kommentaren ist nichts zu tun
        } else {
            LCParserCommand command;

            // Validatoren testen und gefundene Befehle speichern
            for (int i = 0; i < validators->count(); ++i) {
                if (validators->at(i)(*it, &command)) {
                    commands->append(command);
                    break;
                }
            }

            // Kein Befehl gefunden wenn command noch LCUnknownCommand ist
            // Dann nach Fehlertyp suchen und speichern
            if (command.command == LCUnknownCommand) {
                errors->append(findLineError(*it, it - codeLines.begin()));
            }
        }

        ++it;
    }

    // Keine Fehler wenn errors leer ist
    return errors->isEmpty();
}

/* ==================== */
/* findLineError        */
/* ==================== */

LCParserError LCParser::findLineError(QString string, int line) {
    // TODO: Fehlererkennung implementieren
    return LCParserError(string, line, LCErrNone);
}

/* ==================== */
/* moveExpValidator     */
/* ==================== */

bool LCParser::moveExpValidator(QString string, LCParserCommand * command) {
    if (command != NULL && command->parameterCount >= 2) {
        if (LCParser::moveExp->exactMatch(string.toUpper())) {
            QStringList list = LCParser::moveExp->capturedTexts();

            // Liste enthält [0] ganzen string, [1] MOVE, [2] parameter 1, [3] parameter 2
            command->command        = LCMoveCommand;
            command->parameter[0]   = list[2].toInt();
            command->parameter[1]   = list[3].toInt();

            return true;
        }
    }
    return false;
}

/* ==================== */
/* powerExpValidator    */
/* ==================== */

bool LCParser::powerExpValidator(QString string, LCParserCommand * command) {
    if (command != NULL && command->parameterCount >= 1) {
        if (LCParser::powerExp->exactMatch(string.toUpper())) {
            QStringList list = LCParser::powerExp->capturedTexts();

            // Liste enthält [0] ganzen string, [1] LASER, [2] parameter 1
            command->command        = LCPowerCommand;
            command->parameter[0]   = list[2].toInt();

            return true;
        }
    }
    return false;
}