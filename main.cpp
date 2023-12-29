#include <iostream>
#include "source/FlightManagement.h"
int main() {
    FlightManagement fm = FlightManagement();
    // FEN -> RRG 220 stops??
    // CPO -> LYB 413 ????
    // Low Traffic Airports for testing: CPO, LYB, GKA, CYB


    cout << fm.reachableAirportsInXStops("ORY", 2);
    return 0;
}
