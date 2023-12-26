//
// Created by duarte on 18-12-2023.
//

#ifndef AED_PROJECT2_FLIGHTMANAGEMENT_H
#define AED_PROJECT2_FLIGHTMANAGEMENT_H


using namespace std;

#include "Graph.h"
#include <string>
#include "unordered_map"
#include <unordered_set>
#include <map>


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
    int nFlightsCity(string city, string country);
    int nFlightsAirline(string airline);

    //iv
    //In one flight
    int nCountriesFromAirport();
    int nCountriesFromCity();

    //v

    int reachableCountriesFromAirport();


    //vi
    int reachableAirportsInXStops(string source, int x);
    int reachableCitiesInXStops(string source, int x);
    int reachableCountriesInXStops(string source, int x);

    //vii
    void maxTrip(const string& airportCode);

    //viii
    void topTrafficAirports(int k);

    //ix
    unordered_set<string> essentialAirports();//articulation points

    /**Best Flight Option*/

    vector<map<string,string>> bestFlightAirportCode(const string& sourceCode, const string& targetCode);
    void bestFlightAirportName(const string sourceName, const string& targetName);

    void bestFlightCity(const string sourceName, const string& targetName);

    void bestFlightGeographical();

    //Combinations of these


};


#endif //AED_PROJECT2_FLIGHTMANAGEMENT_H
