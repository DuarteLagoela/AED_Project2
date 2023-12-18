//
// Created by duarte on 18-12-2023.
//

#ifndef AED_PROJECT2_FLIGHTMANAGEMENT_H
#define AED_PROJECT2_FLIGHTMANAGEMENT_H


using namespace std;

#include "Graph.h"
#include <string>
#include "unordered_map"

struct airport {
    string code;
    string name;
    string city;
    string country;
    double latitude;
    double longitude;

};

struct airline {
    string code;
    string name;
    string callsign;
    string country;
};

class FlightManagement {
private:
    unordered_map<string, airport> airportMap;
    unordered_map<string, airline> airlineMap;

    Graph<airport> airNetwork;

public:
    FlightManagement();
    void addAirport(airport airport);
};


#endif //AED_PROJECT2_FLIGHTMANAGEMENT_H
