//
// Created by duarte on 18-12-2023.
//

#ifndef AED_PROJECT2_DATASETLOADER_H
#define AED_PROJECT2_DATASETLOADER_H

using namespace std;

#include <string>
class FlightManagement;

class DataSetLoader {

public:
    DataSetLoader() = default;

    void airportLoader(const string& airports_csv, FlightManagement& fm);
    void airlineLoader(const string& airports_csv, FlightManagement& fm);
    void flightsLoader(const string& airports_csv, FlightManagement& fm);

};


#endif //AED_PROJECT2_DATASETLOADER_H
