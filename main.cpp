#include <iostream>
#include "source/FlightManagement.h"
int main() {
    FlightManagement fm = FlightManagement();



    cout << fm.reachableAirportsInXStops("ORY", 2);
    return 0;
}
