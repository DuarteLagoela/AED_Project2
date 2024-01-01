//
// Created by ruixa on 30/12/2023.
//

#ifndef AED_PROJECT2_MENU_H
#define AED_PROJECT2_MENU_H


#include <limits>
#include <cmath>
#include <climits>

class Menu {
public:
    void mainMenu(FlightManagement fm);
private:
    void statistictsMenu(FlightManagement fm);
    void bestFlightMenu(FlightManagement fm);

    // Auxiliar functions
    void invalidInputHandler(vector<int> inputs, int last);
    Vertex<string>* airportCodeHandler(FlightManagement fm);
    void sourceTargetOptions(FlightManagement fm, vector<Vertex<string>*> &vector);
    };

void Menu::mainMenu(FlightManagement fm) {
    cout << "1. Check network statistics" << endl
        << "2. Get best flight option" << endl
        << "0. Quit service" << endl;
    int input;
    while(!(cin >> input) || (input < 0 || input > 2)){
        invalidInputHandler({0,1},2);
    }
    if (input == 0){
        return;
    }
    else if (input == 1){
        statistictsMenu(fm);
    }
    else if (input == 2){
        bestFlightMenu(fm);
    }
    //mainMenu(fm);
}

void Menu::statistictsMenu(FlightManagement fm){
    cout << "1. Get the global number of airports and flights" << endl
        << "2. Find out how many flights take off from an airport and the number of different airlines" << endl
        << "3. Discover how many flights land and take off from every city or the number of flights each airline has" << endl
        << "4. Get the number of different countries that a given airport or city flies to" << endl
        << "5. Check the number of distinct destinations for a given airport" << endl
        << "6. Find out the number of reachable destinations (airports, cities or countries) from a given airport with a max number of lay-overs" << endl
        << "7. Discover which is the trip with the greatest number of stops" << endl
        << "8. Check which are the top-k airport with greatest number of flights" << endl
        << "9. Get the number of essential airports of the network - articulation points" << endl
        << "0. Quit" << endl;
    int input;
    while (!(cin >> input) || input < 0 || input > 9){
        invalidInputHandler({0,1,2,3,4,5,6,7,8},9);
    }

    int input2;
    switch(input) {
        case 0:
            mainMenu(fm);
            break;
        case 1:
            cout << "1. Number of airports" << endl
                 << "2. Number of flights" << endl
                 << "0. Quit" << endl;

            while (!(cin >> input2) || input2 < 0 || input2 > 2) {
                invalidInputHandler({0, 1}, 2);
            }

            switch (input2) {
                case 0:
                    statistictsMenu(fm);
                    break;
                case 1:
                    fm.nAirports();
                    break;
                case 2:
                    fm.nAvailableFlights();
                    break;
            }
            break;

        case 2:
            fm.nFlightsFromAirport(airportCodeHandler(fm));
            break;
        case 3:
            cout << "1. Number of flights per city" << endl
                 << "2. Number of flights per airline" << endl
                 << "0. Quit" << endl;

            while (!(cin >> input2) || input2 < 0 || input2 > 2) {
                invalidInputHandler({0, 1}, 2);
            }

            switch (input2) {
                case 0:
                    statistictsMenu(fm);
                    break;
                case 1:
                    fm.nFlightsCity();
                    break;
                case 2:
                    fm.nFlightsAirline();
                    break;
            }
            break;
        case 4:
            cout << "1. From airport" << endl
                 << "2. From city" << endl
                 << "0. Quit" << endl;

            while (!(cin >> input2) || input2 < 0 || input2 > 2) {
                invalidInputHandler({0, 1}, 2);
            }

            switch (input2) {
                case 0:
                    statistictsMenu(fm);
                    break;
                case 1:
                    fm.nCountriesFromAirport(airportCodeHandler(fm));
                    break;
                case 2:{
                    string city, country, code = "";
                    cout << "Country:";
                    cin.ignore();
                    while(true){
                        getline(cin, country);
                        for (auto x : fm.getAirportMap()){
                            if (x.second.country == country){
                                goto endLoops;
                            }
                        }
                        cout << "Invalid country. Please insert a valid country:";
                    }
                    endLoops:
                    cout << "City:";
                    while(true){
                        getline(cin, city);
                        for (auto x : fm.getAirportMap()){
                            if (x.second.country == country && x.second.city == city) {
                                goto endLoops2;
                            }
                        }
                        cout << "Invalid city. Please enter a valid city:";
                    }
                    endLoops2:
                    fm.nCountriesFromCity(city, country);
                }
            }
            break;
        case 5:
            cout << "1. Airports" << endl
                 << "2. Cities" << endl
                 << "3. Countries"<< endl
                 << "0. Quit" << endl;

            while (!(cin >> input2) || input2 < 0 || input2 > 3) {
                invalidInputHandler({0, 1, 2}, 3);
            }

            switch (input2) {
                case 0:
                    statistictsMenu(fm);
                    break;
                case 1:
                    fm.reachableAirportsFromAirport(airportCodeHandler(fm));
                    break;
                case 2:
                    fm.reachableCitiesFromAirport(airportCodeHandler(fm));
                    break;
                case 3:
                    fm.reachableCountriesFromAirport(airportCodeHandler(fm));
                    break;
            }break;
        case 6:{
            cout << "1. Reachable airports" << endl
                 << "2. Reachable cities" << endl
                 << "3. Reachable countries" << endl
                 << "0. Quit" << endl;

            while (!(cin >> input2) || input2 < 0 || input2 > 3) {
                invalidInputHandler({0, 1, 2}, 3);
            }

            string source;
            int stops;
            if (input2 != 0) {
                cout << "Airport code:";
                while (true) {
                    cin >> source;
                    cout << endl;
                    if (fm.getAirNetwork().findVertex(source) == NULL) {
                        cout << "Invalid airport. Please insert a valid airport code:";
                        invalidInputHandler({},0);
                    }
                    else break;
                }
                cout << "Max number of stops:";
                while (!(cin >> stops) || stops <= 0) {
                    cout << "Invalid input. Please insert a positive number:";
                    cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            switch (input2) {
                case 0:
                    statistictsMenu(fm);
                    break;
                case 1:
                    fm.reachableAirportsInXStops(source, stops);
                    break;
                case 2:
                    fm.reachableCitiesInXStops(source, stops);
                    break;
                case 3:
                    fm.reachableCountriesInXStops(source, stops);
                    break;
            }
            break;}
        case 7:
            fm.maxTrip();
            break;
        case 8:{
            int k = 0;
            cout << "Insert a value for k:";
            while(!(cin >> k) || k <= 0){
                invalidInputHandler({},0);
                cout << "Invalid number. Please insert a positive number:";
            }
            fm.topTrafficAirports(k);
        }break;
        case 9:
            fm.essentialAirports();
            break;
    }
    string dummy;
    cout << "(Enter anything to continue):";
    cin >> dummy;
    statistictsMenu(fm);
}

double toRadians(double degree) {
    return degree * (M_PI / 180.0);
}

double haversineDistance(double lat1, double lon1, double lat2, double lon2) {
    // Radius of the Earth in kilometers
    const double earthRadius = 6371.0;

    // Convert latitude and longitude from degrees to radians
    lat1 = toRadians(lat1);
    lon1 = toRadians(lon1);
    lat2 = toRadians(lat2);
    lon2 = toRadians(lon2);

    // Calculate differences
    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    // Haversine formula
    double a = sin(dlat / 2.0) * sin(dlat / 2.0) +
               cos(lat1) * cos(lat2) * sin(dlon / 2.0) * sin(dlon / 2.0);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));

    // Calculate the distance
    double distance = earthRadius * c;

    return distance;
}

void Menu::bestFlightMenu(FlightManagement fm){
    vector<Vertex<string>*> source;
    vector<Vertex<string>*> target;

    cout << "Select origin by:" << endl;
    sourceTargetOptions(fm, source);
    cout << "Select destination by:" << endl;
    sourceTargetOptions(fm, target);

    cout << "Would you like to specify which airlines to fly?(y/n)";
    string x;
    while(true){
        cin >> x;
        if (x == "y" || x == "n") break;
        else {
            cout << "Invalid answer. Please insert 'y' for yes or 'n' for no:";
            invalidInputHandler({},0);
        }
    }
    unordered_set<string> airlines;
    if (x == "y"){
        while(true){
            string airline;
            cout << "New airline (insert 'q' to stop):";
            cin >> airline;
            if (airline == "q") break;
            auto finder = fm.getAirlineMap().find(airline);
            if (finder == fm.getAirlineMap().end()) cout << "Invalid airline" << endl;
            else airlines.insert(finder->first);
        }
    }
    if (airlines.empty()) airlines.insert("ignore");

    cout << "Would you like to set a max number of different airlines?(y/n)";
    while(true){
        cin >> x;
        if (x == "y" || x == "n") break;
        else {
            cout << "Invalid answer. Please insert 'y' for yes or 'n' for no:";
            invalidInputHandler({}, 0);
        }
    }
    int maxAirlines = INT_MAX;
    if (x == "y"){
        cout << "Number of different airlines:";
        while(!(cin >> maxAirlines) || maxAirlines <= 0){
            invalidInputHandler({},0);
            cout << "Invalid number of airlines. Please insert a positive number:";
        }
    }

    auto ans = fm.bestFlightOption(source,target, maxAirlines,airlines);
    if (ans.empty()) cout << "There aren't any flights available.";
    else {
        int i = 1;
        cout << "There are " << ans.size() << " flight options with " << ans[0].size() - 1 << " stops each:" << endl;
        for (auto option: ans) {
            cout << "Option " << i++ << ":" << endl;
            for (int i = 1; i < option.size(); i++) cout << i << ". " << option[i - 1].first << " -> " << option[i].first << " via " << option[i].second << endl << endl;

        }
    }
    string dummy;
    cout << "(Enter anything to continue):";
    cin >> dummy;
    bestFlightMenu(fm);
}

void Menu::invalidInputHandler(vector<int> inputs, int last){
    if (last != 0) {
        cout << "Invalid input. Accepted inputs: ";
        for (int x: inputs) {
            cout << x << ", ";
        }
        cout << last << "." << endl;
    }
    cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Vertex<string>* Menu::airportCodeHandler(FlightManagement fm){
    cout << "Airport code:";
    string source;
    while (true) {
        cin >> source;
        cout << endl;
        if (fm.getAirNetwork().findVertex(source) == NULL) {
            cout << "Invalid airport. Please insert a valid airport code:";
            invalidInputHandler({}, 0);
        } else return fm.getAirNetwork().findVertex(source);

    }
}

void Menu::sourceTargetOptions(FlightManagement fm, vector<Vertex<string>*> &vector){
    cout << "1. Airport Code" << endl
        << "2. Airport Name" << endl
        << "3. City" << endl
        << "4. Coordinates" << endl
        << "5. Quit" << endl;
    int input;
    while (!(cin >> input) || input < 0 || input > 5){
        invalidInputHandler({0,1,2,3,4},5);
    }
    string a,b;
    if (input == 0) mainMenu(fm);
    else if (input == 1) {
        cout << "Airport code:";
        while (true) {
            cin >> a;
            auto airport = fm.getAirNetwork().findVertex(a);
            if (airport == NULL) {
                cout << "Invalid airport. Please insert a valid airport code:";
                invalidInputHandler({},0);
            }
            else {
                vector.push_back(airport);
                break;
            }
        }

    }
    else if (input == 2) {
        cout << "Airport name:";
        cin.ignore();
        string code = "";
        while(true){
            //cin.ignore();
            getline(cin, a);
            for (auto x : fm.getAirportMap()){
                if (x.second.name == a) {
                    code = x.second.code;
                }
            }
            if (code == "") {
                cout << "Airport not found. Please enter a valid airport name:";
                //invalidInputHandler({},0);
            }
            else {
                auto s = fm.getAirNetwork().findVertex(code);
                vector.push_back(s);
                break;
            }
        }

    }
    if (input == 3) {
        cout << "Country:";
        cin.ignore();
        bool found = false;
        while(true){
            getline(cin, a);
            for (auto x : fm.getAirportMap()){
                if (x.second.country == a){
                    found = true;
                }
            }
            if (found) break;
            cout << "Invalid country. Please insert a valid country:";
        }

        found = false;
        cout << "City:";
        while(true){
            getline(cin, b);
            for (auto x : fm.getAirportMap()){
                if (x.second.country == a && x.second.city == b) {
                    vector.push_back(fm.getAirNetwork().findVertex(x.first));
                    found = true;
                }
            }
            if (found) break;
            cout << "Invalid city. Please enter a valid city:";
        }
    }
    else if (input == 4) {
        double lat, lon;
        cout << "Latitude:";
        while (!(cin >> lat) || lat < -90 || lat > 90){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid latitude. Please insert a number in range (-90,90):";
        }
        cout << "Longitude:";
        while (!(cin >> lon) || lon < -180 || lon > 180) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid longitude. Please insert a number in range (-180,180):";
        }
        double min = INT_MAX;
        airport closest;
        for (auto airport : fm.getAirportMap()){
            double distance = haversineDistance(lat,lon,airport.second.latitude,airport.second.longitude);
            if (distance < min){
                min = distance;
                closest = airport.second;
            }
        }
        auto s = fm.getAirNetwork().findVertex(closest.code);
        cout << "Closest airport: " << closest.name << " (" << closest.code << ") in " << closest.city
             << ", " <<  closest.country << endl;
        vector.push_back(s);
    }
    else if (input == 5){
        mainMenu(fm);
    }

}
#endif //AED_PROJECT2_MENU_H
