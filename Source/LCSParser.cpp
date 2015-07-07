#include "LCSParser.h"

#include <iostream>
#include <sstream>
#include <locale>

/* ---------------------------------------------------------------------------------------------------------------- */
/* Reguläre Ausdrücke (Beschreibung siehe Ende der Headerdatei)                                                     */
/* ---------------------------------------------------------------------------------------------------------------- */

const std::regex * LCSParser::moveExp    = new std::regex("^\\s*(MOVE)\\s+(-?\\d{1,4})\\s*,\\s*(-?\\d{1,4})(?:\\s*\\#+.*|\\s*)$",
                                                          std::regex::icase | std::regex::collate);
const std::regex * LCSParser::powerExp   = new std::regex("^\\s*(LASER)\\s+(ON|OFF)(?:\\s*\\#+.*|\\s*)$",
                                                          std::regex::icase | std::regex::collate);
const std::regex * LCSParser::commentExp = new std::regex("(^\\s*\\#+.*$|^\\s*$)",
                                                          std::regex::icase | std::regex::collate);

/* ---------------------------------------------------------------------------------------------------------------- */
/* Parser Error                                                                                                     */
/* ---------------------------------------------------------------------------------------------------------------- */

/* ======================= */
/* Konstruktoren           */
/* ======================= */

LCSParserError::LCSParserError(std::string code, std::string msg, int line, LCSErrorCode error) {
    this->code  = code;
    this->msg   = msg;
    this->line  = line;
    this->error = error;
}

LCSParserError::LCSParserError() {
    code  = "";
    msg   = "";
    line  = -1;
    error = LCSErrNone;
}

/* ---------------------------------------------------------------------------------------------------------------- */
/* Parser Command                                                                                                   */
/* ---------------------------------------------------------------------------------------------------------------- */

/* ======================= */
/* Konstruktoren           */
/* ======================= */

LCSParserCommand::LCSParserCommand(LCSCommandCode command, int * parameter, int parameterCount, int line) {
    this->command           = command;
    this->parameter         = parameter;
    this->parameterCount    = parameterCount;
    this->line              = line;
}

LCSParserCommand::LCSParserCommand() {
    command           = LCSCmdUnknown;
    parameter         = (int *) malloc(sizeof(int) * 2);  // Größe für MOVE Befehl
    parameterCount    = 2;
    line              = -1;
}

/* ---------------------------------------------------------------------------------------------------------------- */
/* Parser Klasse                                                                                                    */
/* ---------------------------------------------------------------------------------------------------------------- */

/* ======================= */
/* Konstruktor             */
/* ======================= */

LCSParser::LCSParser() {
    validators = new std::vector<validatorFunction>();

    validators->push_back(LCSParser::moveExpValidator);
    validators->push_back(LCSParser::powerExpValidator);

    // Weitere Validatoren können in erbenden Klassen hinzugefügt werden.
}

/* ======================= */
/* Parser                  */
/* ======================= */

bool LCSParser::parse(std::string code, std::vector<LCSParserCommand> * commands, std::vector<LCSParserError> * errors) {
    if (commands == nullptr || errors == nullptr) {
        return false;
    }

    std::stringstream  codeStream(code);
    std::string        tempString;
    int                lineCounter = 1;     // Zeile startet bei 1

    // Über die Zeilen iterieren
    while(std::getline(codeStream, tempString)) {
        if (tempString.empty() || std::regex_match(tempString, *LCSParser::commentExp)) {
            // Leerer String oder Kommentar
            // Überspringen
        } else {
            LCSParserCommand command;

            // Validatoren testen und Befehl speichern
            for (const validatorFunction validator : *(validators)) {
                if (validator(tempString, &command)) {
                    command.line = lineCounter;
                    commands->push_back(command);
                    break;
                }
            }

            // Kein Befehl gefunden wenn 'command' noch LCSCmdUnknown ist
            // Dann nach Fehlertyp suchen und speichern
            if (command.command == LCSCmdUnknown) {
                errors->push_back(findLineError(tempString, lineCounter));
            }
        }

        lineCounter++;
    }

    return errors->empty();
}

/* ======================= */
/* Fehlererkennung         */
/* ======================= */

LCSParserError LCSParser::findLineError(std::string code, int line) {
    std::stringstream   msg;
    LCSErrorCode        err = LCSErrNone;

    msg << "Syntaxfehler: " << code;

    return LCSParserError(code, msg.str(), line, err);
}

/* ======================= */
/* Validierungsmethoden    */
/* ======================= */

bool LCSParser::moveExpValidator(std::string code, LCSParserCommand * command) {
    if (command != nullptr && command->parameterCount >= 2) {
        std::smatch match;

        if (std::regex_match(code, match, *LCSParser::moveExp) && match.size() == 4) {
            // 'match' enthält [0] ganzen string, [1] MOVE, [2] parameter 1, [3] parameter 2
            command->command        = LCSCmdEngine;
            command->parameter[0]   = atoi(match.str(2).c_str());
            command->parameter[1]   = atoi(match.str(3).c_str());

            return true;
        }
    }

    return false;
}

bool LCSParser::powerExpValidator(std::string code, LCSParserCommand * command) {
    if (command != nullptr && command->parameterCount >= 2) {
        std::smatch match;
        static std::locale loc;

        if (std::regex_match(code, match, *LCSParser::powerExp) && match.size() == 3) {
            // Liste enthält [0] ganzen string, [1] LASER, [2] parameter 1
            command->command = LCSCmdLaser;

            //if (std::tolower(match.str(2), loc).compare("on") == 0) {
            if (match.str(2) .compare("on") == 0 ||
                match.str(2) .compare("ON") == 0 ||
                match.str(2) .compare("oN") == 0 ||
                match.str(2) .compare("On") == 0) {
                command->parameter[0] = 1;
            } else {
                command->parameter[0] = 0;
            }

            return true;
        }
    }

    return false;
}
