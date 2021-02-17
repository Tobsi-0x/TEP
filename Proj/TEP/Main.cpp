#include <Windows.h>
#include <iostream>

#include "MainWindow.h"

int main(int argc, char* argv[]) {

    MainWindow mainWindow;
    mainWindow.run();

    std::cout << "\n================================================"
        << "\nEnter any key (not space or enter) to quit: ";
    int a;
    std::cin >> a;

    return 0;
}

/* ==========DEV LOG==========

dev_001:

 - added & linked dependencies.
 - a
 - a



*/