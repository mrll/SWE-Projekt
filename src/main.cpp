//
// Created by Matthias Röll, Marc Wüst on 09.05.15.
//

#include <iostream>
#include "Model/LCParser.h"
#include "View/LCUserInterface.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    LCUserInterface userInterface;
    userInterface.show();
    return a.exec();
}
