//
// Created by ruixa on 30/12/2023.
//

#ifndef AED_PROJECT2_MENU_H
#define AED_PROJECT2_MENU_H


#include <limits>

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
        case 6:
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
                cout << "Airport code:" << endl;
                while (true) {
                    cin >> source;
                    if (fm.airNetwork.findVertex(source) == NULL) {
                        cout << "Invalid airport. Please insert a valid airport code:";
                        continue;
                    }
                }
                cout << "Max number of stops:";
                while ((!cin >> stops) || stops <= 0) {
                    cout << "Invalid input. Please insert a non-negative number:";
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
            break;
        case 7:
        case 8:
        case 9:
            break;
    }
}



void Menu::bestFlightMenu(FlightManagement fm){

}

void Menu::invalidInputHandler(vector<int> inputs, int last){
    cout << "Invalid input. Accepted inputs: ";
    for (int x : inputs){
        cout << x << ", ";
    }
    cout << last << "." << endl;
    cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

#endif //AED_PROJECT2_MENU_H
