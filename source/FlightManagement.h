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

    Graph<string> airNetwork;

public:
    FlightManagement();
    void addAirport(airport airport);
    void addAirline(airline airline);
    void addFlight(string sourceCode, string targetCode, string airlineCode);

    /**Functionalities*/

    //Modify return type and parameters as needed

    //i
    int nAirports();
    int nAvailableFlights();

    //ii
    int nFlightsFromAirport(); //n flights and different companies

    //iii
    int nFlightsCity();
    int nFlightsAirline();

    //iv
    //In one flight
    int nCountriesFromAirport();
    int nCountriesFromCity();

    //v

    int reachableCountriesFromAirport();


    //vi
    int reachableAirportsInXStops();
    int reachableCitiesInXStops();
    int reachableCountriesInXStops();

    //vii
    void maxTrip(const string& airportCode);

    //viii
    void topTrafficAirports(int k);

    //ix
    void essentialAirports();//articulation points

    /**Best Flight Option*/

    void bestFlightAirportCode(const string& sourceCode, const string& targetCode);
    void bestFlightAirportName(const string sourceName, const string& targetName);

    void bestFlightCity(const string sourceName, const string& targetName);

    void bestFlightGeographical();

    //Combinations of these


};


#endif //AED_PROJECT2_FLIGHTMANAGEMENT_H
