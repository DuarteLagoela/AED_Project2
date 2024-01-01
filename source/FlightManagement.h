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
    string code;/**@param code**/
    string name;/**@param name**/
    string city;/**@param city**/
    string country;/**@param country**/
    double latitude;/**@param latitude**/
    double longitude;/**@param longitude**/

};

struct airline {
    string code;/**@param code**/
    string name;/**@param name**/
    string callsign;/**@param callsign**/
    string country;/**@param country**/
};

class FlightManagement {
private:
    Graph<string> airNetwork;/**@param airNetwork**/
    unordered_map<string, airport> airportMap;/**@param airportMap**/
    unordered_map<string, airline> airlineMap;/**@param airlineMap**/
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
    int nAirports();/**@return Total number of airports**/
    int nAvailableFlights();/**@return Total number of flights**/

    //ii
    int nFlightsFromAirport(Vertex<string>* src_ptr); /**@return Number of flights out of an airport and from how many different airlines**///n flights and different companies

    //iii
    void nFlightsCity();/**@brief Number of flights per city**/
    void nFlightsAirline();/**@brief Number of flights per airline**/

    //iv
    //In one flight
    int nCountriesFromAirport(Vertex<string>* src_ptr);/**@return Number of different countries that a given airport flies to**/
    int nCountriesFromCity(string city, string country);/**@return Number of different countries that a given city flies to**/

    //v

    int reachableCountriesFromAirport(Vertex<string>* src_airport);/**@return Number of countries available for a given airport**/
    int reachableCitiesFromAirport(Vertex<string>* src_airport);/**@return Number of cities available for a given airport**/
    int reachableAirportsFromAirport(Vertex<string>* src_airport);/**@return Number of airports available for a given airport**/


    //vi
    void reachableAirportsInXStops(string source, int x);/**@brief Number of reachable airports from a given airport and a maximum number of stops**/
    void reachableCitiesInXStops(string source, int x);/**@brief Number of reachable cities from a given airport and a maximum number of stops**/
    void reachableCountriesInXStops(string source, int x);/**@brief Number of reachable countries from a given airport and a maximum number of stops**/

    //vii
    void maxTrip();/**@brief Trips with the most amount of stops and the corresponding pair (source/destination) **/


    //viii
    void topTrafficAirports(int k);/**@brief Top-k airports with the greatest number of flights**/

    //ix
    void essentialAirports();/**@brief Airports that are essential to the network's circulation capability**///articulation points

    /**Best Flight Option*/
    vector<vector<pair<string,string>>> bestFlightOption(const vector<Vertex<string>*> sourceVector, const vector<Vertex<string>*> targetVector, int maxAirlines, unordered_set<string> wantedAirlines);/**@brief Filtered best flight options**/

    void bestFlightAirportName(const string sourceName, const string& targetName);/**@brief The best trip option within a given airport**/

    void bestFlightCity(const string sourceName, const string& targetName);/**@brief The best trip option within a given city**/

    void bestFlightGeographical();/**@brief The best trip option close to a given location**/

    //Combinations of these


};


#endif //AED_PROJECT2_FLIGHTMANAGEMENT_H
