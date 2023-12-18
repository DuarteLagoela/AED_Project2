//
// Created by duarte on 18-12-2023.
//

#include "FlightManagement.h"

#include "DataSetLoader.h"

void FlightManagement::addAirport(airport airport) {
    airportMap[airport.code] = airport;
}

FlightManagement::FlightManagement() {
    DataSetLoader dsl;

    dsl.airportLoader("dataset/airports.csv", *this);
}
