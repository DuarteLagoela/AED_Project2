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

void DataSetLoader::airlineLoader(const string& airports_csv, FlightManagement &fm) {

}

void DataSetLoader::flightsLoader(const string& airports_csv, FlightManagement &fm) {

}
