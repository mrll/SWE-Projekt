#ifndef LCSPARSER_H
#define LCSPARSER_H

#include <string>
#include <vector>
#include <regex>

/* ---------------------------------------------------------------------------------------------------------------- */
/* Enumerationen                                                                                                    */
/* ---------------------------------------------------------------------------------------------------------------- */

/**
 * Fehlertypenenumaration
 */
typedef enum {
    LCSErrNone = 0,             /**< Kein Fehler (Platzhalter bei Initialisierung)  */
    LCSErrSyntax = 1,           /**< Syntaxfehler (Allgemein)                       */
    LCSErrMoveSyntax = 2,       /**< Syntaxfehler (Move)                            */
    LCSErrPowerSyntax = 3       /**< Syntaxfehler (Power)                           */
} LCSErrorCode;

/**
 * Befehlsenumeration
 */
typedef enum {
    LCSCmdUnknown = 0,          /**< Unbekannter Befehl (Platzhalter bei Initialisierung/Validierung)   */
    LCSCmdEngine = 1,           /**< Move Befehl  (MOVE 100, 200)                                       */
    LCSCmdLaser = 2             /**< Power Befehl (LASER ON)                                            */
} LCSCommandCode;

/* ---------------------------------------------------------------------------------------------------------------- */
/* Parser Error / Parseer Command Klassen                                                                           */
/* ---------------------------------------------------------------------------------------------------------------- */

/**
 * Klasse zum Speichern von Fehlertypen und Daten
 */
class LCSParserError {

public:
    LCSParserError(std::string code, std::string msg, int line, LCSErrorCode error);
    LCSParserError();

    std::string code;       /**< Codestring     */
    std::string msg;        /**< Fehlermeldung  */
    int line;               /**< Zeile          */
    LCSErrorCode error;     /**< Fehlercode     */
};

/**
 * Klasse zum Speichern von Behlen und Parametern
 */
class LCSParserCommand {

public:
    LCSParserCommand(LCSCommandCode command, int * parameter, int parameterCount, int line);
    LCSParserCommand();

    LCSCommandCode     command;             /**< Befehl             */
    int             * parameter;            /**< Parameter          */
    int               parameterCount;       /**< Parameterannzahl   */
    int               line;                 /**< Zeile              */
};

/* ---------------------------------------------------------------------------------------------------------------- */
/* Typendeklaration Validierungsfunktion                                                                            */
/* ---------------------------------------------------------------------------------------------------------------- */

/**
 * Typendefinition für Validierungsfunktionen
 *
 * @param string String zum Prüfen
 * @param LCParserCommand* Zeiger auf einen Command zum speichern der gefundenen Werte
 *
 * @see LCParser::moveExpValidator LCParser::powerExpValidator
 *
 * @return Erfolgreiche Validierung
 */
typedef bool(*validatorFunction)(std::string, LCSParserCommand *);

/* ---------------------------------------------------------------------------------------------------------------- */
/* Parser Klasse                                                                                                    */
/* ---------------------------------------------------------------------------------------------------------------- */

class LCSParser
{
public:
    /**
     * Standartkonstruktor
     *
     * Der Konstruktor initialisiert den 'validators' Vector.
     * Dieser kann in erbenden Klassen um neue Befehle erweitert werden.
     */
    LCSParser();

    /**
     * Parserfunktion
     *
     * Prüft den übergebenen Code zeilenweise mit allen Validierungsfunktionen in 'validators'.
     * Dabei werden die Befehle in 'commands' und etwaige Fehler in 'errors' gespeichert.
     *
     * Gibt false zurück wenn 'commands' oder 'errors' gleich NULL sind.
     *
     * @param code Der zu parsende Codestring
     * @param commands vector zum Speichern gefundener Befehle
     * @param errors vector zum Speichern gefundener Fehler
     *
     * @return true wenn keine Fehler auftauchten.
     */
    bool parse(std::string code, std::vector<LCSParserCommand> * commands, std::vector<LCSParserError> * errors);

    /**
     * Fehleranalyse
     *
     * Erstellt einen Fehlebericht anhand eines LCSParserError Objekts
     *
     * @param string Zeilenstring
     * @param line Zeilennummer
     *
     * @return Fehlerobjekt
     */
    LCSParserError findLineError(std::string code, int line);

    static const std::regex * moveExp;              /**< MOVE Befehl Ausdruck               */
    static const std::regex * powerExp;             /**< LASER Befehl Ausdruck              */
    static const std::regex * commentExp;           /**< Kommentar Ausdruck                 */

protected:
    std::vector<validatorFunction> * validators;    /**< Feld mit Validierungsfunktionen    */

    /* Um den Parser mit neuen Syntaxelementen zu erweitern. Kann im Konstruktor einer erbenden Klasse
     * der Vector 'validators' um weitere reguläre Ausdrücke erweitert werden. Diese müssen dazu in
     * einer Funktion des 'validatorFunction' Typs geprüft werden.
     */

private:
    static bool moveExpValidator(std::string code, LCSParserCommand * command);
    static bool powerExpValidator(std::string code, LCSParserCommand * command);
};

/* ---------------------------------------------------------------------------------------------------------------- */
/* Reguläre Ausdrücke                                                                                               */
/* ---------------------------------------------------------------------------------------------------------------- */

/*
 * MOVE Expression - ^\s*(MOVE)\s+(\d{1,4})\s*,\s*(\d{1,4})(?:\s*\#+.*|\s*)$
 *
 * ^\s*                     - Anfang der Zeile mit optionalen Leerzeichen
 * (MOVE)                   - Gruppe 1: MOVE
 * \s+                      - Mindstens 1 Leerzeichen
 * (-?\d{1,4})              - Gruppe 2: Zahl zwischen -9999 und 9999
 * \s*,\s*                  - Trennung durch Komma mit optionalen Leerzeichen
 * (-?\d{1,4})              - Gruppe 3: Zahl zwischen -9999 und 9999
 * (?:\s*\#+.*|\s*)         - Entweder ein Kommentarstring (# + Irgendwas) oder Leerzeichen (optional)
 * $                        - Ende der Zeile
 */

/*
 * LASER Expression - ^\s*(LASER)\s+(ON|OFF)(?:\s*\#+.*|\s*)$
 *
 * ^\s*                     - Anfang der Zeile mit optionalen Leerzeichen
 * (LASER)                  - Gruppe 1: LASER
 * \s+                      - Mindstens 1 Leerzeichen
 * (ON|OFF)                 - Gruppe 2: ON oder OFF
 * (?:\s*\#+.*|\s*)         - Entweder ein Kommentarstring (# + Irgendwas) oder Leerzeichen (optional)
 * $                        - Ende der Zeile
 */

/*
 * COMMENT Expression - (^\s*\#+.*$|^\s*$)
 *
 * ^\s*                     - Anfang der Zeile mit optionalen Leerzeichen
 * \#+.*                    - Kommentarstring (# + Irgendwas)
 * $                        - Ende der Zeile
 * |                        - logisches Oder
 * \s*$                     - Verhindert die Erkennung von leeren Zeilen bei der Fehlererkennung (findLineError())
 */

/* RegEx Tester: http://www.regexr.com */

#endif // LCSPARSER_H
