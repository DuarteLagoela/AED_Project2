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
    /**@param code**/
    string code;
    /**@param name**/
    string name;
    /**@param city**/
    string city;
    /**@param country**/
    string country;
    /**@param latitude**/
    double latitude;
    /**@param longitude**/
    double longitude;

};

struct airline {
    /**@param code**/
    string code;
    /**@param name**/
    string name;
    /**@param callsign**/
    string callsign;
    /**@param country**/
    string country;
};

class FlightManagement {
private:
    /**@param airNetwork**/
    Graph<string> airNetwork;
    /**@param airportMap**/
    unordered_map<string, airport> airportMap;
    /**@param airlineMap**/
    unordered_map<string, airline> airlineMap;
public:
    Graph<string> getAirNetwork(){return airNetwork;}
    unordered_map<string, airport> &getAirportMap(){return airportMap;}
    unordered_map<string, airline> &getAirlineMap(){return airlineMap;}
    FlightManagement();
    void addAirport(airport airport);
    void addAirline(airline airline);
    void addFlight(string sourceCode, string targetCode, string airlineCode);

    /**Functionalities*/

    //Modify return type and parameters as needed

    //i
    /**@return Total number of airports**/
    int nAirports();
    /**@return Total number of flights**/
    int nAvailableFlights();

    //ii
    /**@return Number of flights out of an airport and from how many different airlines**///n flights and different companies
    int nFlightsFromAirport(Vertex<string>* src_ptr);

    //iii
    /**@brief Number of flights per city**/
    void nFlightsCity();
    /**@brief Number of flights per airline**/
    void nFlightsAirline();

    //iv
    //In one flight
    /**@return Number of different countries that a given airport flies to**/
    int nCountriesFromAirport(Vertex<string>* src_ptr);
    /**@return Number of different countries that a given city flies to**/
    int nCountriesFromCity(string city, string country);

    //v
    /**@return Number of countries available for a given airport**/
    int reachableCountriesFromAirport(Vertex<string>* src_airport);
    /**@return Number of cities available for a given airport**/
    int reachableCitiesFromAirport(Vertex<string>* src_airport);
    /**@return Number of airports available for a given airport**/
    int reachableAirportsFromAirport(Vertex<string>* src_airport);


    //vi
    /**@brief Number of reachable airports from a given airport and a maximum number of stops**/
    void reachableAirportsInXStops(string source, int x);
    /**@brief Number of reachable cities from a given airport and a maximum number of stops**/
    void reachableCitiesInXStops(string source, int x);
    /**@brief Number of reachable countries from a given airport and a maximum number of stops**/
    void reachableCountriesInXStops(string source, int x);

    //vii
    /**@brief Trips with the most amount of stops and the corresponding pair (source/destination) **/
    void maxTrip();


    //viii
    /**@brief Top-k airports with the greatest number of flights**/
    void topTrafficAirports(int k);

    //ix
    /**@brief Airports that are essential to the network's circulation capability**///articulation points
    void essentialAirports();

    /**Best Flight Option*/
    /**@brief Filtered best flight options**/
    vector<vector<pair<string,string>>> bestFlightOption(const vector<Vertex<string>*> sourceVector, const vector<Vertex<string>*> targetVector, int maxAirlines, unordered_set<string> wantedAirlines);
/**@brief The best trip option within a given airport**/
    void bestFlightAirportName(const string sourceName, const string& targetName);
/**@brief The best trip option within a given city**/
    void bestFlightCity(const string sourceName, const string& targetName);
/**@brief The best trip option close to a given location**/
    void bestFlightGeographical();

    //Combinations of these


};


#endif //AED_PROJECT2_FLIGHTMANAGEMENT_H
