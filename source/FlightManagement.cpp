//
// Created by duarte on 18-12-2023.
//

#include "FlightManagement.h"

void FlightManagement::addAirport(airport airport) {
    airportMap[airport.code] = airport;
}
