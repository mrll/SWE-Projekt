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

#pragma mark Enums
/* ---------------------------------------------------------------------------------------------------------------- */

/**
 * Fehlertypenenumaration
 */
typedef enum {
    LCErrNone = 0,              /**< Kein Fehler (Platzhalter bei Initialisierung)  */
    LCErrSyntax = 1,            /**< Syntaxfehler                                   */
    LCErrParamaterType = 2,     /**< Falscher Parametertyp                          */
    LCErrParameterCount = 3     /**< Falsche Parameteranzahl                        */
} LCErrorCode;

/**
 * Befehlsenumeration
 */
typedef enum {
    LCUnknownCommand = 0,       /**< Unbekannter Befehl (Platzhalter bei Initialisierung/Validierung)   */
    LCMoveCommand = 1,          /**< Move Befehl  (MOVE 100, 200)                                       */
    LCPowerCommand = 2          /**< Power Befehl (LASER ON)                                            */
} LCCommandCode;

#pragma mark LCParserError
/* ---------------------------------------------------------------------------------------------------------------- */

/**
 * Klasse zum Speichern von Fehlertypen und Daten
 */
class LCParserError {

public:
    LCParserError(QString string, int line, LCErrorCode code);
    LCParserError();

    QString string;         /**< Fehlerstring   */
    int line;               /**< Zeile          */
    LCErrorCode code;       /**< Fehlercode     */
};

#pragma mark LCParserCommand
/* ---------------------------------------------------------------------------------------------------------------- */

/**
 * Klasse zum Speichern von Behlen und Parametern
 */
class LCParserCommand {

public:
    LCParserCommand(LCCommandCode command, int * parameter, int parameterCount);
    LCParserCommand();

    LCCommandCode     command;              /**< Befehl             */
    int             * parameter;            /**< Parameter          */
    int               parameterCount;       /**< Parameterannzahl   */
};

#pragma mark Typedefs
/* ---------------------------------------------------------------------------------------------------------------- */

/**
 * Typendefinition für Validierungsfunktionen
 *
 * @param QString String zum Prüfen
 * @param LCParserCommand* Zeiger auf einen Command zum speichern der gefundenen Werte
 *
 * @see LCParser::moveExpValidator LCParser::powerExpValidator
 *
 * @return Erfolgreiche Validierung
 */
typedef bool(*validatorFunction)(QString, LCParserCommand *);

#pragma mark LCParser
/* ---------------------------------------------------------------------------------------------------------------- */

/**
 * Parserklasse
 */
class LCParser {

public:
    /**
     * Standartkonstruktor
     *
     * Der Konstruktor initialisiert den 'validators' Vector.
     * Dieser kann in erbenden Klassen um neue Befehle erweitert werden.
     */
    LCParser();

    /**
     * Parserfunktion
     *
     * Prüft den übergebenen Code zeilenweise mit allen Validierungsfunktionen in 'validators'.
     * Dabei werden die Befehle in 'commands' und etwaige Fehler in 'errors' gespeichert.
     *
     * Gibt false zurück wenn 'commands' oder 'errors' gleich NULL sind.
     *
     * @param code Der zu parsende Codestring
     * @param commands QVector zum Speichern gefundener Befehle
     * @param errors QVector zum Speichern gefundener Fehler
     *
     * @return true wenn keine Fehler auftauchten.
     */
    bool parse(QString code, QVector<LCParserCommand> * commands, QVector<LCParserError> * errors);

    /**
     * Fehleranalyse
     *
     * Sucht nach der Fehlerursache in einer Zeile. Und gibt einen LCParserError zurück.
     *
     * Die Fehler werden in folgender Reihenfolge gesucht:
     * * Parametertyp
     * * Parameteranzahl
     * * Syntax
     *
     * @param string Zeilenstring
     * @param line Zeilennummer
     *
     * @return Fehlerobjekt
     */
    LCParserError findLineError(QString string, int line);

    static const QRegExp * moveExp;             /**< MOVE Befehl Ausdruck               */
    static const QRegExp * powerExp;            /**< LASER Befehl Ausdruck              */
    static const QRegExp * commentExp;          /**< Kommentar Ausdruck                 */

protected:
    QVector<validatorFunction> * validators;    /**< Feld mit Validierungsfunktionen    */

private:
    static bool moveExpValidator(QString string, LCParserCommand * command);
    static bool powerExpValidator(QString string, LCParserCommand * command);
};

#pragma mark RegEx Descriptions
/* ---------------------------------------------------------------------------------------------------------------- */

/*
 * MOVE Expression - ^\s?(MOVE)\s+(\d{1,4})\s*,\s*(\d{1,4})(?:\s*\#+.*|\s*)$
 *
 * ^\s?                     - Anfang der Zeile mit optionalen Leerzeichen
 * (MOVE)                   - Gruppe 1: MOVE
 * \s+                      - Mindstens 1 Leerzeichen
 * (\d{1,4})                - Gruppe 2: Zahl zwischen 0 und 9999
 * \s*,\s*                  - Trennung durch Komma mit optionalen Leerzeichen
 * (\d{1,4})                - Gruppe 3: Zahl zwischen 0 und 9999
 * (?:\s*\#+.*|\s*)         - Entweder ein Kommentarstring (# + Irgendwas) oder Leerzeichen (optional)
 * $                        - Ende der Zeile
 */

/*
 * LASER Expression - ^\s?(LASER)\s+(ON|OFF)(?:\s*\#+.*|\s*)$
 *
 * ^\s?                     - Anfang der Zeile mit optionalen Leerzeichen
 * (LASER)                  - Gruppe 1: LASER
 * \s+                      - Mindstens 1 Leerzeichen
 * (ON|OFF)                 - Gruppe 2: ON oder OFF
 * (?:\s*\#+.*|\s*)         - Entweder ein Kommentarstring (# + Irgendwas) oder Leerzeichen (optional)
 * $                        - Ende der Zeile
 */

/*
 * COMMENT Expression - \s?\#+.*$
 *
 * ^\s?                     - Anfang der Zeile mit optionalen Leerzeichen
 * \#+.*                    - Kommentarstring (# + Irgendwas)
 * $                        - Ende der Zeile
 */

/* RegEx Tester: http://www.regexr.com */

#endif //SWE_PROJEKT_PARSER_H
