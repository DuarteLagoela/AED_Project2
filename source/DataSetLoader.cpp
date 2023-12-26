//
// Created by duarte on 18-12-2023.
//

#include "DataSetLoader.h"

#include "FlightManagement.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

void DataSetLoader::airportLoader(const string& airports_csv, FlightManagement &fm) {

    std::ifstream in(airports_csv);

    if (!in.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    string code;
    string name;
    string city;
    string country;
    string latitudeStr;
    string longitudeStr;

    double latitude = 0;
    double longitude = 0;

    std::string line;
    std::getline(in, line);

    while (std::getline(in, line) )
    {

        std::istringstream ss(line);

        std::getline(ss, code, ',');
        std::getline(ss, name, ',');
        std::getline(ss, city, ',');
        std::getline(ss, country, ',');
        std::getline(ss, latitudeStr, ',');
        std::getline(ss, longitudeStr, ',');

        latitude = stod(latitudeStr);
        longitude = stod(longitudeStr);

        airport airport = {code, name, city, country, latitude, longitude};
        fm.addAirport(airport);


    }

}

void DataSetLoader::airlineLoader(const string& airlines_csv, FlightManagement &fm) {

    std::ifstream in(airlines_csv);

    if (!in.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }



    string code;
    string name;
    string callsign;
    string country;

    std::string line;
    std::getline(in, line);

    while (std::getline(in, line) )
    {

        std::istringstream ss(line);

        std::getline(ss, code, ',');
        std::getline(ss, name, ',');
        std::getline(ss, callsign, ',');
        std::getline(ss, country, ',');




        airline airline = {code, name, callsign, country};
        fm.addAirline(airline);


    }
}

void DataSetLoader::flightsLoader(const string& flights_csv, FlightManagement &fm) {

    std::ifstream in(flights_csv);

    if (!in.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }



    string sourceCode;
    string targetCode;
    string airlineCode;

    std::string line;
    std::getline(in, line);

    while (std::getline(in, line) )
    {

        std::istringstream ss(line);

        std::getline(ss, sourceCode, ',');
        std::getline(ss, targetCode, ',');
        std::getline(ss, airlineCode, ',');

        fm.addFlight(sourceCode, targetCode, airlineCode);
    }

}
