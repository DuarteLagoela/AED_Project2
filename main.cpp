#include <iostream>
#include "source/FlightManagement.h"
#include "source/Menu.h"

int main() {
    FlightManagement fm = FlightManagement();
    Menu menu;
    cout << "Welcome to your personal flight booking service!" << endl
         << "How can we help you today?" << endl;
    menu.mainMenu(fm);
    return 0;
}
