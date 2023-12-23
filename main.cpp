#include <iostream>
#include "source/FlightManagement.h"
int main() {
    FlightManagement fm = FlightManagement();
    fm.reachableCitiesFromAirport("JFK");
    return 0;
}
