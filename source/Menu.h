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
    void statistictsMenu(FlightManagement fm);
    void bestFlightMenu(FlightManagement fm);
    void invalidInputHandler(vector<int> inputs, int last);
};

void Menu::mainMenu(FlightManagement fm) {
    cout << "Welcome to your personal flight booking service!" << endl
        << "How can we help you today?" << endl
        << "1. Check network statistics" << endl
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

        case 2:


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
        case 5:
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
            cout << "k: ";
            cin >> k;
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

// Haversine distance calculation function
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
        cout << "Select source by:" << endl <<
             "1. Airport code" << endl <<
             "2. Airport name" << endl <<
             "3. City" << endl <<
             "4. Coordinates" << endl <<
             "0. Quit" << endl;
        int input;
        while (!(cin >> input) || input < 0 || input > 4){
            invalidInputHandler({0,1,2,3},4);
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
                    source.push_back(airport);
                    break;
                }
            }

        }
        else if (input == 2) {
            cout << "Airport name:";
            cin.ignore();
            string code = "";
            while(true){
                getline(cin, a);
                for (auto x : fm.getAirportMap()){
                    if (x.second.name == a) {
                        code = x.second.code;
                    }
                }
                if (code == "") {
                    cout << "Airport not found. Please enter a valid airport name:";
                    invalidInputHandler({},0);
                }
                else {
                    auto s = fm.getAirNetwork().findVertex(code);
                    source.push_back(s);
                    break;
                }
            }

        }
        if (input == 3) {
            string code = "";
            cout << "Country:";
            cin.ignore();
            while(true){
                getline(cin, a);
                for (auto x : fm.getAirportMap()){
                    if (x.second.country == a){
                        goto endLoops;
                    }
                }
                cout << "Invalid country. Please insert a valid country:";
            }
            endLoops:
            cout << "City:";
            while(true){
                getline(cin, b);
                for (auto x : fm.getAirportMap()){
                    if (x.second.country == a && x.second.city == b) {
                        auto s = x.second.code;
                        source.push_back(fm.getAirNetwork().findVertex(s));
                        break;
                    }
                }
                cout << "Invalid city. Please enter a valid city:" << endl;
                invalidInputHandler({},0);
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
            source.push_back(s);
        }

        cout << "Select target by:" << endl <<
             "1. Airport code" << endl <<
             "2. Airport name" << endl <<
             "3. City" << endl <<
             "4. Coordinates" << endl;

        cin >> input;

        if (input == 1) {
            cout << "Airport code:";
            cin >> a;
            auto s = fm.getAirNetwork().findVertex(a);
            if (s == NULL) {
                cout << "Airport not found." << endl;
                //fm.bestFlightOption();
                return;
            }
            else target.push_back(s);
        }
        if (input == 2) {
            cout << "Airport name:";
            cin.ignore();
            getline(cin, a);
            string code = "";
            for (auto x : fm.getAirportMap()){
                if (x.second.name == a) {
                    code = x.second.code;
                }
            }
            if (code == "") {
                cout << "Airport not found." << endl;
                //fm.bestFlightOption();
                return;
            }
            else {
                auto s = fm.getAirNetwork().findVertex(code);
                target.push_back(s);
            }
        }
        if (input == 3) {
            cout << "Country:";
            cin.ignore();
            getline(cin, a);
            cout << "City:";
            getline(cin, b);
            bool found = false;
            for (auto x : fm.getAirportMap()){
                if (x.second.country == a && x.second.city == b) {
                    auto s = x.second.code;
                    target.push_back(fm.getAirNetwork().findVertex(s));
                    found = true;
                }
            }
            if (!found) {
                cout << "Invalid city." << endl;
                //fm.bestFlightOption();
                return;
            }
        }
        if (input == 4) {
            double lat, lon;
            while (true) {
                cout << "Latitude:";
                if (std::cin >> lat) {
                    break;
                }
                else {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid latitude." << std::endl;
                }
            }
            while (true) {
                cout << "Longitude:";
                if (std::cin >> lon) {
                    break;
                }
                else {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid longitude." << std::endl;
                }
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
            target.push_back(s);
        }

        cout << "Would you like to specify which airlines to fly?(y/n)";
        string x;
        cin >> x;
        unordered_set<string> airlines;
        if (x == "y"){
            while(true){
                string airline;
                cout << "New airline (insert 'q' to stop):";
                cin >> airline;
                if (airline == "q") break;
                auto tomas = fm.getAirlineMap().find(airline);
                if (tomas == fm.getAirlineMap().end()) cout << "Invalid airline" << endl;
                else airlines.insert(tomas->first);
            }
        }
        else airlines.insert("ignore");

        cout << "Would you like to set a max number of different airlines?(y/n)";
        cin >> x;
        int maxAirlines = INT_MAX;
        if (x == "y"){
            cout << "Number of different airlines:";
            cin >> maxAirlines;
        }

        auto ans = fm.bestFlightOption(source,target, maxAirlines,airlines);
        if (ans.empty()) cout << "There aren't any flights available.";
        else {
            int i = 1;
            cout << "There are " << ans.size() << " flight options with " << ans[0].size() - 1 << " stops each:" << endl;
            for (auto option: ans) {
                cout << "Option " << i++ << ":" << endl;
                for (int i = 1; i < option.size(); i++) {
                    cout << i << ". " << option[i - 1].first << " -> " << option[i].first << " via " << option[i].second
                         << endl;
                }
                cout << endl;
            }
        }


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
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

#endif //AED_PROJECT2_MENU_H
