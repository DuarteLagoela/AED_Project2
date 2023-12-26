#include <iostream>
#include "source/FlightManagement.h"
int main() {
    FlightManagement fm = FlightManagement();

    // Low Traffic Airports for testing: CPO, LYB, GKA, CYB

    // long x = fm.nFlightsCity("Porto","Portugal");
    std::cout << "Breakpoint here" << endl;

    auto y = fm.bestFlightAirportCode("OPO","LIS");
    // auto aYO = fm.essentialAirports().size();
    std::cout << "Breakpoint here" << endl;
    return 0;
}
