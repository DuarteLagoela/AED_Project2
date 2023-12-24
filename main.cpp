#include <iostream>
#include "source/FlightManagement.h"
int main() {
    FlightManagement fm = FlightManagement();
    fm.reachableAirportsFromAirport("JFK");
    return 0;
}
