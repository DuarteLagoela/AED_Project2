//
// Created by duarte on 18-12-2023.
//

#include "FlightManagement.h"

#include "DataSetLoader.h"
#include <iostream>
#include <iomanip>
#include <set>
void FlightManagement::addAirport(airport airport) {
    airportMap[airport.code] = airport;
    airNetwork.addVertex(airport.code);
}

FlightManagement::FlightManagement() {
    DataSetLoader dsl;

    dsl.airportLoader("dataset/airports.csv", *this);
    dsl.airlineLoader("dataset/airlines.csv", *this);
    dsl.flightsLoader("dataset/flights.csv", *this);

}

void FlightManagement::addAirline(airline airline) {
    airlineMap[airline.code] = airline;
}

void FlightManagement::addFlight(string sourceCode, string targetCode, string airlineCode) {

    airNetwork.addEdge(sourceCode, targetCode, airlineCode);


}

int FlightManagement::nFlightsFromAirport(const string& airportCode) {

    Vertex<string>* src_ptr = airNetwork.findVertex(airportCode);
    set<string> airlineSet;
    int res = 0;
    if (!src_ptr){
        cout << "Invalid airport code.";
        return 0;
    }


    cout << left << setw(54) << "Destination:" << setw(10) << "Airline:" << endl;

    for (const Edge<string>& e : src_ptr->getAdj()) {
        string destinationCode = e.getDest()->getInfo();
        airport destinationAirport = airportMap[destinationCode];
        string airlineCode = e.getAirlineCode();
        cout << left << setw(4) << destinationCode << setw(50) << destinationAirport.name
             << setw(4) << airlineCode << airlineMap[airlineCode].name << endl;
        airlineSet.insert(e.getAirlineCode());
        res++;
    }

    cout << "There are " << res << " flights available from " << airlineSet.size() << " different airlines." << endl;

    return res;
}

int FlightManagement::reachableCountriesFromAirport(const string& airportCode) {
    Vertex<string>* src_airport= airNetwork.findVertex(airportCode);

    if (!src_airport) {
        cout << "Invalid airport" << endl;
        return 0;
    }

    set<string> countrySet;

    for (auto e : src_airport->getAdj()) {
        string country = airportMap[e.getDest()->getInfo()].country;
        auto p = countrySet.insert(country);
    }

    cout << "Available countries:" << endl;
    for (auto c : countrySet) {
        cout << c << endl;
    }

    int nCountries = countrySet.size();

    cout << "You can travel to " << nCountries << " different countries departing from the " << airportMap[airportCode].name << " airport." << endl;
    return nCountries;
}

int FlightManagement::reachableCitiesFromAirport(const string &airportCode) {
    Vertex<string>* src_airport= airNetwork.findVertex(airportCode);

    if (!src_airport) {
        cout << "Invalid airport" << endl;
        return 0;
    }

    set<string> citySet;

    for (auto e : src_airport->getAdj()) {
        string country = airportMap[e.getDest()->getInfo()].city;
        auto p = citySet.insert(country);
    }

    cout << "Available countries:" << endl;
    for (auto c : citySet) {
        cout << c << endl;
    }

    int nCities = citySet.size();

    cout << "You can travel to " << nCities << " different cities departing from the " << airportMap[airportCode].name << " airport." << endl;
    return nCities;

}

int FlightManagement::reachableAirportsFromAirport(const string &airportCode) {

    Vertex<string>* src_airport= airNetwork.findVertex(airportCode);

    if (!src_airport) {
        cout << "Invalid airport" << endl;
        return 0;
    }

    set<string> airportSet;

    for (auto e : src_airport->getAdj()) {
        string airportCode = e.getDest()->getInfo();
        auto p = airportSet.insert(airportCode);
    }

    cout << "Available airports:" << endl;
    for (auto c : airportSet) {
        cout << c << " " << airportMap[c].name << endl;
    }

    int nAirports = airportSet.size();

    cout << "You can travel to " << nAirports << " different airports departing from the " << airportMap[airportCode].name << " airport." << endl;
    return nAirports;
}

void FlightManagement::topTrafficAirports(int k) {

    set<pair<int, string>> flightsAirport;

    for (auto& v : airNetwork.getVertexSet()) {
        flightsAirport.insert({v->getAdj().size(), v->getInfo()});
    }

    cout << "Top " << k << " airports with greatest traffic" << endl;
    cout << left <<setw(43) << "\nAirport:" << setw(20) << "Number of Flights:" << endl;

    int n = 0;
    auto end = flightsAirport.end();
    end--;
    for (auto it = end; it != flightsAirport.begin(); it--) {
        n++;
        cout << left << n << "- " << setw(4)<< it->second << setw(35) << airportMap[it->second].name << setw(20) << it->first << endl;

        if (n == k){ return;}
    }



}
