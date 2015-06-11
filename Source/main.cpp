//
// Created by Matthias Röll, Marc Wüst on 09.05.15.
//

#include "View/LCUserInterface.h"
#include "Controller/LCController.h"

int main(int argc, char *argv[]) {
    LCController * controller = new LCController();

    QApplication a(argc, argv);
    LCUserInterface userInterface;
    userInterface.controller = controller;
    userInterface.show();
    return a.exec();
}
