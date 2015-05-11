//
// Created by Matthias Röll, Marc Wüst on 09.05.15.
//

#ifndef SWE_PROJEKT_PARSER_H
#define SWE_PROJEKT_PARSER_H

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVector>
#include <QtCore/QRegExp>
#include <QtCore/QMap>

//#include "LCState.h"

#pragma mark Enums

typedef enum {
    LCErrNone = 0,              // No Error (on init)
    LCErrSyntax = 1,            // Syntaxerror
    LCErrParamaterType = 2,     // Wrong parameter type
    LCErrParameterCount = 3     // Wrong parameter count
} LCErrorCode;

typedef enum {
    LCUnknownCommand = 0,       // Unknown command (on init)
    LCMoveCommand = 1,          // Move command (MOVE 100, 200)
    LCPowerCommand = 2          // Power command (LASER ON)
} LCCommandCode;

#pragma mark LCParserError

class LCParserError {

public:
    LCParserError(QString string, int line, LCErrorCode code);
    LCParserError();

    QString string;         // Errorstring
    int line;               // Line number
    LCErrorCode code;       // Error code
};

#pragma mark LCParserCommand

class LCParserCommand {

public:
    LCParserCommand(LCCommandCode command, int parameter1, int parameter2);
    LCParserCommand();

    LCCommandCode command;  // Command
    int parameter1;         // Parameter 1
    int parameter2;         // Parameter 2 (Only LCMoveCommand)
};

#pragma mark Typedefs

typedef bool(*validatorFunction)(QString, LCParserCommand *);

#pragma mark LCParser

class LCParser {

public:
    LCParser();

    bool parse(QString code, QVector<LCParserCommand> * commands, QVector<LCParserError> * errors);
    LCParserError findLineError(QString string, int line);

#pragma mark RegEx Declaration

    static const QRegExp * moveExp;
    static const QRegExp * powerExp;
    static const QRegExp * commentExp;

protected:
#pragma mark RegEx Function Table

    QVector<validatorFunction> * validators;

private:
#pragma mark RegEx Functions

    static bool moveExpValidator(QString string, LCParserCommand * command);
    static bool powerExpValidator(QString string, LCParserCommand * command);
};

#pragma mark RegEx Descriptions

/*
 * MOVE Expression - ^\s?(MOVE)\s+(\d){1,4}\s*,(\s)*(\d){1,4}(?:\s*\#+.*|\s*)$
 *
 * ^\s?                     - Begin of line with optional whitespaces
 * (MOVE)                   - Group 1: Word MOVE
 * \s+                      - One whitespace at minimum
 * (\d){1,4}                - Group 2: One to four digits
 * \s*,\s*                  - Comma seperated with optional whitespaces in between
 * (\d){1,4}                - Group 3: One to four digits
 * (?:\s*\#+.*|\s*)         - Either a comment (optional whitespaces + # + something) or just optional whitespaces
 * $                        - End of line
 */

/*
 * LASER Expression - ^\s?(LASER)\s+(ON|OFF)(?:\s*\#+.*|\s*)$
 *
 * ^\s?                     - Begin of line with optional whitespaces
 * (LASER)                  - Group 1: Word LASER
 * \s+                      - One whitespace at minimum
 * (ON|OFF)                 - Group 2: Word ON or OFF
 * (?:\s*\#+.*|\s*)         - Either a comment (optional whitespaces + # + something) or just optional whitespaces
 * $                        - End of line
 */

/*
 * COMMENT Expression - \s?\#+.*$
 *
 * ^\s?                     - Begin of line with optional whitespaces
 * \#+.*                    - # + something
 * $                        - End of line
 */

/* RegEx Tester: http://www.regexr.com */

#endif //SWE_PROJEKT_PARSER_H
