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
    /**@brief Data parsers**/
    DataSetLoader() = default;
    /**@param airports_csv Path for airports data**/
    void airportLoader(const string& airports_csv, FlightManagement& fm);
    /**@param airlines_csv Path for airlines data**/
    void airlineLoader(const string& airlines_csv, FlightManagement& fm);
    /**@param flights_csv Path for flights data**/
    void flightsLoader(const string& flights_csv, FlightManagement& fm);

};


#endif //AED_PROJECT2_DATASETLOADER_H
