#include <iostream>
#include "source/FlightManagement.h"
#include "source/Menu.h"

int main() {
    FlightManagement fm = FlightManagement();
    // FEN -> RRG 220 stops??
    // CPO -> LYB 413 ????
    // Low Traffic Airports for testing: CPO, LYB, GKA, CYB
    Menu menu;
    menu.mainMenu(fm);
    // long x = fm.nFlightsCity("Porto","Portugal");
    //std::cout << fm.essentialAirports().size();
    //fm.bestFlightOption();
    // auto aYO = fm.essentialAirports().size();
    std::cout << "Breakpoint here" << endl;


    return 0;
}
