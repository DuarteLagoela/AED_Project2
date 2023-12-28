//
// Created by duarte on 18-12-2023.
//

#include <iostream>
#include <set>
#include <unordered_set>
#include <map>
#include "FlightManagement.h"
#include <utility>
#include "DataSetLoader.h"
#include <iostream>
#include <iomanip>
#include <set>
#include <cmath>
#include <climits>

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

    auto v = airNetwork.findVertex(targetCode);
    v->increaseInDegree();
}

// 3. Statistics of the network
// ii
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

// iii
void FlightManagement::nFlightsCity() {

    // Get all cities
    set<std::pair<std::string,std::string>> cities;
    for (auto airport : airportMap){
        cities.insert(make_pair(airport.second.country,airport.second.city));
    }

    for (auto city : cities){
        cout << city.second << ", " << city.first << " has ";
        int res = 0;
        // Get City Airports
        vector<string> cityAirports;
        for (auto p : airportMap){
            if (p.second.country == city.first && p.second.city == city.second) {
                cityAirports.push_back(p.first);
            }
        }

        for (string airportCode : cityAirports){
            auto v = airNetwork.findVertex(airportCode);
            res += v->getIndegree();
            res += (int) v->getAdj().size();
        }
        cout << res << " flights." << endl;
    }

}

// Number of flights per airline
void FlightManagement::nFlightsAirline() {
    string airlineCode;
    for (auto airline : airlineMap){
        airlineCode = airline.first;
        cout << "Airline " << airline.second.name << " (" << airlineCode << ") has ";
        int res = 0;
        for (auto v : airNetwork.getVertexSet()){
            for (auto e : v->getAdj()){
                if (e.getAirlineCode() == airlineCode) {
                    res++;
                }
            }
        }
        cout << res << " flights." << endl;
    }
}

// v
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

// vi
// Number of reachable airports from a given airport with X stops
int FlightManagement::reachableAirportsInXStops(string source, int x) { // DONE
    int res = 0;
    auto v = airNetwork.findVertex(source);
    if (v == NULL) {
        cout << "Airport " << source << " doesn't exist" << endl;
        return -1;
    };
    for (auto a : airNetwork.getVertexSet()) {
        a->setVisited(false);
    }
    queue<Vertex<string>*> q;
    q.push(v);
    v->setVisited(true);
    int dist = 0;
    while (!q.empty() && dist <= x) {
        int help = q.size();
        for (int i = 0; i < help; i++) {
            auto c = q.front();
            q.pop();
            if (dist <= x) {
                res++;
            }
            for (auto e : c->getAdj()) {
                auto d = e.getDest();
                if (!d->isVisited()) {
                    d->setVisited(true);
                    q.push(d);
                }
            }
        }
        dist++;
    }
    return res - 1;

}

// Number of reachable cities from a given airport with X stops
int FlightManagement::reachableCitiesInXStops(string source, int x) {
    std::set<string> res;
    auto v = airNetwork.findVertex(source);
    if (v == NULL){
        cout << "Airport " << source << " doesn't exist" << endl;
        return -1;
    }
    for (auto a : airNetwork.getVertexSet()) {
        a->setVisited(false);
    }
    queue<Vertex<string>*> q;
    q.push(v);
    v->setVisited(true);
    int dist = 0;
    while (!q.empty() && dist <= x) {
        int help = q.size();
        for (int i = 0; i < help; i++) {
            auto c = q.front();
            q.pop();
            if (dist <= x) {
                auto city = airportMap[c->getInfo()].city;
                res.insert(city);
            }
            for (auto e : c->getAdj()) {
                auto d = e.getDest();
                if (!d->isVisited()) {
                    d->setVisited(true);
                    q.push(d);
                }
            }
        }
        dist++;
    }
    return (int) res.size() - 1;

}

// Number of reachable countries from a given airport with X stops
int FlightManagement::reachableCountriesInXStops(string source, int x) {
    std::set<string> res;
    auto v = airNetwork.findVertex(source);
    if (v == NULL){
        cout << "Airport " << source << " doesn't exist" << endl;
        return -1;
    }
    for (auto a : airNetwork.getVertexSet()) {
        a->setVisited(false);
    }
    queue<Vertex<string>*> q;
    q.push(v);
    v->setVisited(true);
    int dist = 0;
    while (!q.empty() && dist <= x) {
        int help = q.size();
        for (int i = 0; i < help; i++) {
            auto c = q.front();
            q.pop();
            if (dist <= x) {
                auto country = airportMap[c->getInfo()].country;
                res.insert(country);
            }
            for (auto e : c->getAdj()) {
                auto d = e.getDest();
                if (!d->isVisited()) {
                    d->setVisited(true);
                    q.push(d);
                }
            }
        }
        dist++;
    }
    return (int) res.size() - 1;
}
// viii
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

// ix - 312
bool inStack(Vertex<string>* w,stack<string> s);
void dfs_art(Graph<string> &g, Vertex<string> *v, stack<string> &s, unordered_set<string> &l, int &i);

unordered_set<string> FlightManagement::essentialAirports() {
    unordered_set<string> res;
    stack<string> s;
    int i = 0;
    for(auto v : airNetwork.getVertexSet()){
        v->setVisited(false);
    }
    for(auto v : airNetwork.getVertexSet()){
        if(!v->isVisited()){
            dfs_art(airNetwork, v, s, res, i);
        }
    }
    return res;
}

void dfs_art(Graph<string> &g, Vertex<string> *v, stack<string> &s, unordered_set<string> &l, int &i){
    int childCount = 0;
    i++;
    v->setNum(i);
    v->setLow(i);
    v->setVisited(true);
    s.push(v->getInfo());
    for(auto edge : v->getAdj()){
        auto w = edge.getDest();
        if(!w->isVisited()){
            childCount++;
            dfs_art(g, w, s, l, i);
            v->setLow(min(v->getLow(), w->getLow()));
            if(w->getLow() >= v->getNum() && v->getNum() != 1){
                l.insert(v->getInfo());
            }
        }
        else if(inStack(w, s)){
            v->setLow(min(v->getLow(), w->getNum()));
        }
    }
    s.pop();
    if(v->getNum() == 1 && childCount > 1){
        l.insert(v->getInfo());
    }
}

bool inStack(Vertex<string>* w,stack<string> s){
    while(!s.empty()){
        string a = s.top();
        s.pop();
        if(a == w->getInfo())return true;
    }
    return false;
}

// 4. Best flight option
void dfsVisit(Vertex<string> *s, Vertex<string> *t, vector<pair<string,string>> path, vector<vector<pair<string,string>>> &res, string airline, int &cap) {
    path.push_back(make_pair(s->getInfo(),airline));
    if (path.size() > cap) return;
    s->setVisited(true);

    if (s->getInfo() == t->getInfo()) {
        res.push_back(path);
        cap = (int) path.size();
        s->setVisited(false);
        return;
    }

    for (auto & e : s->getAdj()) {
        auto w = e.getDest();
        if (!w->isVisited()){
            dfsVisit(w, t, path, res, e.getAirlineCode(), cap);
        }
    }
}

vector<vector<pair<string,string>>> FlightManagement::bestFlightOption(const vector<Vertex<string>*> sourceVector, const vector<Vertex<string>*> targetVector) {

    vector<vector<pair<string,string>>> final;
    vector<vector<pair<string,string>>> res;

    for(auto source : sourceVector){
        for (auto target : targetVector){

            for (auto v : airNetwork.getVertexSet())
                v->setVisited(false);
            vector<pair<string,string>> path;
            int cap = INT_MAX;
            dfsVisit(source, target, path, res, "", cap);
        }
    }
    int min = INT_MAX;
    for (auto x : res){
        if (x.size() < min) min = x.size();
    }

    for (auto x : res){
        if (x.size() == min) final.push_back(x);
    }
    return final;
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
void FlightManagement::bestFlightOption(){ // TODO: DOESN'T WORK WHEN CITY/COUNTRY HAS SPACES
    vector<Vertex<string>*> source;
    vector<Vertex<string>*> target;
    cout << "Select source by:" << endl <<
        "1. Airport code" << endl <<
        "2. Airport name" << endl <<
        "3. City" << endl <<
        "4. Coordinates" << endl;
    int input;
    cin >> input;

    string a,b;
    if (input == 1) {
        cout << "Airport code:" << endl;
        cin >> a;
        auto s = airNetwork.findVertex(a);
        if (s == NULL) {
            cout << "Airport not found." << endl;
            bestFlightOption();
            return;
        }
        else source.push_back(s);
    }
    if (input == 2) {
        cout << "Airport name:";
        cin >> a;
        string st = NULL;
        for (auto x : airportMap){
            if (x.second.name == a) st = x.second.code;
        }
        auto s = airNetwork.findVertex(st);
        if (s == NULL) {
            cout << "Airport not found." << endl;
            bestFlightOption();
            return;
        }
        else source.push_back(s);
    }
    if (input == 3) {
        cout << "Country:";
        cin >> a;
        cout << "City:";
        cin >> b;

        bool found = false;
        for (auto x : airportMap){
            if (x.second.country == a && x.second.city == b) {
                auto s = x.second.code;
                source.push_back(airNetwork.findVertex(s));
                found = true;
            }
        }
        if (!found) {
            cout << "Invalid city." << endl;
            bestFlightOption();
            return;
        }
    }
    if (input == 4) {
        double lat, lon;
        cout << "Latitude:";
        cin >> lat;
        cout << "Longitude:";
        cin >> lon;
        double min = INT_MAX;
        airport closest;
        for (auto airport : airportMap){
            double distance = haversineDistance(lat,lon,airport.second.latitude,airport.second.longitude);
            if (distance < min){
                min = distance;
                closest = airport.second;
            }
        }
        auto s = airNetwork.findVertex(closest.code);
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
        cout << "Airport code:" << endl;
        cin >> a;
        auto s = airNetwork.findVertex(a);
        if (s == NULL) {
            cout << "Airport not found." << endl;
            bestFlightOption();
            return;
        }
        else target.push_back(s);
    }
    if (input == 2) {
        cout << "Airport name:" << endl;
        cin >> a;
        string st = NULL;
        for (auto x : airportMap){
            if (x.second.name == a) st = x.second.code;
        }
        auto s = airNetwork.findVertex(st);
        if (s == NULL) {
            cout << "Airport not found." << endl;
            bestFlightOption();
            return;
        }
        else target.push_back(s);
    }
    if (input == 3) {
        cout << "Country:" << endl;
        cin >> a;
        cout << "City" << endl;
        cin >> b;
        bool found = false;
        for (auto x : airportMap){
            if (x.second.country == a && x.second.city == b) {
                auto s = x.second.code;
                target.push_back(airNetwork.findVertex(s));
                found = true;
            }
        }
        if (!found) {
            cout << "Invalid city." << endl;
            bestFlightOption();
            return;
        }
    }
    if (input == 4) {
        double lat, lon;
        cout << "Latitude:";
        cin >> lat;
        cout << "Longitude:";
        cin >> lon;
        double min = INT_MAX;
        airport closest;
        for (auto airport : airportMap){
            double distance = haversineDistance(lat,lon,airport.second.latitude,airport.second.longitude);
            if (distance < min){
                min = distance;
                closest = airport.second;
            }
        }
        auto s = airNetwork.findVertex(closest.code);
        cout << "Closest airport: " << closest.name << " (" << closest.code << ") in " << closest.city
             << ", " <<  closest.country << endl;
        target.push_back(s);
    }

    auto ans = bestFlightOption(source,target);
    int i = 1;
    cout << "There are " << ans.size() << " flight options with " << ans[0].size() - 1 << " stops each:" << endl;
    for (auto option : ans) {
        cout << "Option " << i++ << ":" << endl;
        for (int i = 1; i < option.size(); i++) {
            cout << i << ". " << option[i-1].first << " -> "  << option[i].first << " via " << option[i].second << endl;
        }
        cout << endl;
    }
}








