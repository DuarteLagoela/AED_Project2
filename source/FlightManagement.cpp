//
// Created by duarte on 18-12-2023.
//

#include <iostream>
#include <set>
#include <unordered_set>
#include <map>
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
/*
    auto v = airNetwork.findVertex(targetCode);
    v.increaseInDegree();*/
}

// iii
// TODO: Number of flights per city
int FlightManagement::nFlightsCity(std::string city, std::string country) {
    int res = 0;
    // Get City Airports
    vector<string> cityAirports;
    for (auto p : airportMap){
        if (p.second.country == country && p.second.city == city) {
            cityAirports.push_back(p.first);
            std::cout << p.first;
        }
    }

    for (string airportCode : cityAirports){
        auto v = airNetwork.findVertex(airportCode);
        res += v->getIndegree(); // TODO: needs fix to inDegree
        res += (int) v->getAdj().size();
    }
    return res;
}

// Number of flights per airline
int FlightManagement::nFlightsAirline(std::string airlineCode) { // DONE
    int res = 0;
    bool found = false;
    // Get airline
    for (auto p : airlineMap){
        if (p.first == airlineCode) {
            found = true;
            break;
        }
    }
    if (!found){
        cout << "Airline " << airlineCode << " doesn't exist" << endl;
        return -1;
    }
    for (auto v : airNetwork.getVertexSet()){
        for (auto e : v->getAdj()){
            if (e.getAirlineCode() == airlineCode) res++;
        }
    }
    return res;
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

// ix
// TODO: Airports that when removed, areas of the network become unreachable - 308 (esta forma resolve directed graphs, mas este é undirected :/)
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

vector<vector<pair<string,string>>> FlightManagement::bestFlightAirportCode(const std::string &sourceCode, const std::string &targetCode) {
    auto source = airNetwork.findVertex(sourceCode);
    auto target = airNetwork.findVertex(targetCode);
    vector<vector<pair<string,string>>> final;
    vector<vector<pair<string,string>>> res;
    vector<pair<string,string>> path;

    if (source == NULL) {
        cout << "Airport " << sourceCode << " doesn't exist." << endl;
        return res;
    }
    if (target == NULL) {
        cout << "Airport " << targetCode << " doesn't exist." << endl;
        return res;
    }

    for (auto v : airNetwork.getVertexSet())
        v->setVisited(false);

    int cap = INT_MAX;
    dfsVisit(source, target, path, res, "", cap);

    int min = INT_MAX;
    for (auto x : res){
        if (x.size() < min) min = x.size();
    }

    for (auto x : res){
        if (x.size() == min) final.push_back(x);
    }
    return final;
}
/*
void dfsVisit(Vertex<string> *s, Vertex<string> *t, vector<Edge<string>> path, vector<vector<Edge<string>>> &res) {
    s->setVisited(true);
    if (s->getInfo() == t->getInfo()) {
        res.push_back(path);
        s->setVisited(false);
        return;
    }

    for (auto & e : s->getAdj()) {
        auto w = e.getDest();
        if (!w->isVisited()){
            dfsVisit(w, t, path, res);
            path.push_back(e);
        }
    }
}

vector<vector<Edge<string>>> FlightManagement::bestFlightAirportCode(const std::string &sourceCode, const std::string &targetCode) {
    auto source = airNetwork.findVertex(sourceCode);
    auto target = airNetwork.findVertex(targetCode);
    vector<vector<Edge<string>>> final;
    vector<vector<Edge<string>>> res;
    vector<Edge<string>> path;

    if (source == NULL) {
        cout << "Airport " << sourceCode << " doesn't exist." << endl;
        return res;
    }
    if (target == NULL) {
        cout << "Airport " << targetCode << " doesn't exist." << endl;
        return res;
    }

    for (auto v : airNetwork.getVertexSet())
        v->setVisited(false);

    dfsVisit(source, target, path, res);

    int min = INT_MAX;
    for (auto x : res){
        if (x.size() < min) min = x.size();
    }

    for (auto x : res){
        if (x.size() == min) final.push_back(x);
    }
    return final;
}
*/


/* BFS
vector<vector<Vertex<string>>> FlightManagement::bestFlightAirportCode(const std::string &sourceCode, const std::string &targetCode) {
    auto source = airNetwork.findVertex(sourceCode);
    auto target = airNetwork.findVertex(targetCode);

    vector<vector<Vertex<string>>> res;

    if (source == NULL) {
        cout << "Airport " << sourceCode << " doesn't exist." << endl;
        return res;
    }
    if (target == NULL) {
        cout << "Airport " << targetCode << " doesn't exist." << endl;
        return res;
    }

    queue<Vertex<string> *> q;
    for (auto v : airNetwork.getVertexSet())
        v->setVisited(false);
    q.push(source);
    source->setVisited(true);
    while (!q.empty()) {
        vector<Vertex<string>*> path;
        auto v = q.front();
        q.pop();
        path.push_back(v);
        for (auto & e : v->getAdj()) {
            auto w = e.getDest();
            if ( ! w->isVisited() ) {
                q.push(w);
                w->setVisited(true);
            }
        }
    }
    return res;
}*/













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
