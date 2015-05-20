//
// Created by Matthias Röll, Marc Wüst on 09.05.15.
//

#include <iostream>
#include "LCParser.h"

#pragma mark RegEx
/* ---------------------------------------------------------------------------------------------------------------- */

const QRegExp * LCParser::moveExp      = new QRegExp("^\\s*(MOVE)\\s+(\\d{1,4})\\s*,\\s*(\\d{1,4})(?:\\s*\\#+.*|\\s*)$",
                                                     Qt::CaseSensitive,
                                                     QRegExp::RegExp);
const QRegExp * LCParser::powerExp     = new QRegExp("^\\s*(LASER)\\s+(ON|OFF)(?:\\s*\\#+.*|\\s*)$",
                                                     Qt::CaseSensitive,
                                                     QRegExp::RegExp);
const QRegExp * LCParser::commentExp   = new QRegExp("(^\\s*\\#+.*$|^\\s*$)",
                                                     Qt::CaseSensitive,
                                                     QRegExp::RegExp);

#pragma mark LCParserError
/* ---------------------------------------------------------------------------------------------------------------- */

/* ==================== */
/* Konstruktoren        */
/* ==================== */

LCParserError::LCParserError(QString string, QString error, int line, LCErrorCode code) {
    this->string = string;
    this->error = error;
    this->line = line;
    this->code = code;
}
LCParserError::LCParserError() {
    this->string = "";
    this->error = "";
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
    QString error;
    LCErrorCode code;

    int moveMatch, powerMatch;

    moveMatch = LCParser::moveExp->matchedLength();
    powerMatch = LCParser::powerExp->matchedLength();

    // Testen welche RegEx am besten gepasst hat und Fehlernachricht schreiben.
    // Die Kommentar RegEx wird hier ausgelassen, da die matchedLength bei einem Fehler immer 0 ist.
    // Sollte weder der MOVE noch der LASER Befehl zuteffen wird ein Unbekannter Fehler gemeldet.
    if (moveMatch > powerMatch) {
        code = LCErrMoveSyntax;
        error = "MOVE Syntaxfehler ab Zeichen: " + QString::number(moveMatch + 1); // +1 wegen Basis 0
    } else if (powerMatch > 0) {
        code = LCErrPowerSyntax;
        error = "LASER Syntaxfehler ab Zeichen: " + QString::number(powerMatch + 1);
    } else {
        code = LCErrSyntax;
        error = "Syntaxfehler";
    }

    return LCParserError(string, error, line + 1, code); // Line wird auch inkrementiert, wegen Basis 0
}

/* ==================== */
/* moveExpValidator     */
/* ==================== */

bool LCParser::moveExpValidator(QString string, LCParserCommand * command) {
    if (command != NULL && command->parameterCount >= 2) {
        if (LCParser::moveExp->exactMatch(string.toUpper())) {
            QStringList list = LCParser::moveExp->capturedTexts();
            bool ok;

            // Liste enthält [0] ganzen string, [1] MOVE, [2] parameter 1, [3] parameter 2
            command->command        = LCMoveCommand;
            command->parameter[0]   = list.at(2).toInt(&ok, 10);
            command->parameter[1]   = list.at(3).toInt(&ok, 10);

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
            if (list.at(2).contains("ON", Qt::CaseSensitive)) {
                command->parameter[0] = 1;
            } else {
                command->parameter[0] = 0;
            }

            return true;
        }
    }
    return false;
}
