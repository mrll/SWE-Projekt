//
// Created by Matthias Röll, Marc Wüst on 09.05.15.
//

#include <iostream>
#include "Model/LCParser.h"
#include "View/LCUserInterface.h"

int main(int argc, char *argv[]) {
    QString code;
    code = ""
            "# Box 1\n"
            "LASER OFF\n"
            "MOVE 100, 100   # Line Kommentar Test\n"
            "LASER ON\n"
            "MOVE 150, 100\n"
            "MOVE 150, 150\n"
            "MOVE 100, 150\n"
            "MOVE 100, 100\n"
            "lAsEr off       # Case Insensitivity Test\n"
            "\n"
            "# Box 2\n"
            "MOVE 200, 200\n"
            "LASER ON\n"
            "MOVE 250, 200\n"
            "MOVE 250, 250\n"
            "MOVE 200, 250\n"
            "MOVE 200, 200\n"
            "LASER OFF\n"
            "\n"
            "# Diagonale\n"
            "MOVE 100, 100\n"
            "LASER ON\n"
            "MOVE 250, 250\n"
            "LASER OFF\n"
            "\n"
            "# Fehler Test\n"
            "#\n"
            "MVE 100, 100      # Typo                  (Syntaxfehler)              Fehlercode 1\n"
            "MOVE 100 200      # Typo 2                (Syntaxfehler)\n"
            "LASER 3           # Inkorrekter Befehl 1  (Falscher Parametertyp)     Fehlercode 2\n"
            "MOVE ON, 250      # Inkorrekter Befehl 2  (Falscher Parametertyp)\n"
            "MOVE 100.2 234.4  # Inkorrekter Befehl 3  (Falscher Parametertyp)\n"
            "LASER ON OFF      # Inkorrekter Befehl 4  (Zu viele Parameter)        Fehlercode 3";

    QVector<LCParserError> *errors = new QVector<LCParserError>();
    QVector<LCParserCommand> *commands = new QVector<LCParserCommand>();

    LCParser * parser = new LCParser();

    bool success = parser->parse(code, commands, errors);

    std::cout << "Found " << commands->count() << " commands and " << errors->count() << " errors" << std::endl << std::endl;

    for (int i = 0; i < errors->count(); i++) {
        std::cout << "Error in Line: " << errors->at(i).line << " Type: " << errors->at(i).code << std::endl;
        std::cout << "String: " << errors->at(i).string.toStdString() << std::endl;
        std::cout << "Message: " << errors->at(i).error.toStdString() << std::endl << std::endl;
    }

    return success;

    QApplication a(argc, argv);
    LCUserInterface userInterface;
    userInterface.show();
    return a.exec();
}
