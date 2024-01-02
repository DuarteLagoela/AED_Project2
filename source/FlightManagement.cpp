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
// i
int FlightManagement::nAirports() {
    cout<<"There are "<<airportMap.size()<<" airports." << endl;
    return airportMap.size();
}

int FlightManagement::nAvailableFlights() {
    int n=0;
    for(auto vertex : airNetwork.getVertexSet()){
        n+=vertex->getAdj().size();
    }
    cout<<"There are "<<n<<" available flights." << endl;
    return n;
}

// ii
int FlightManagement::nFlightsFromAirport(Vertex<string>* src_ptr) {

    set<string> airlineSet;
    int res = 0;

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

// iv
int FlightManagement::nCountriesFromAirport(Vertex<string>* sourceAirport) {
    int res = 0;

    if (sourceAirport == nullptr) {
        cout << "Airport not found!" << endl;
        return 0;
    }

    unordered_set<string> visitedCountries;

    for (const Edge<string>& edge : sourceAirport->getAdj()) {
        Vertex<string>* destAirport = edge.getDest();
        string destCountry = airportMap[destAirport->getInfo()].country;

        if (destCountry != airportMap[sourceAirport->getInfo()].country &&
            visitedCountries.find(destCountry) == visitedCountries.end()) {
            visitedCountries.insert(destCountry);
            res++;
        }
    }

    cout << "From the airport " << airportMap[sourceAirport->getInfo()].name << " you can reach " << res << " countries." << endl;

    return res;
}

int FlightManagement::nCountriesFromCity(string city, string country) {
    int res = 0;
    unordered_set<string> visitedCountries;

    for(auto v : airNetwork.getVertexSet()){
        if(airportMap[v->getInfo()].city==city && airportMap[v->getInfo()].country == country){
            for(auto edge : v->getAdj()){
                Vertex<string>* destAirport = edge.getDest();
                string destCountry = airportMap[destAirport->getInfo()].country;

                if (destCountry != airportMap[v->getInfo()].country &&
                    visitedCountries.find(destCountry) == visitedCountries.end()) {
                    visitedCountries.insert(destCountry);
                    res++;
                }
            }
        }}
    cout << "From the city " << city << " you can reach " << res << " countries." << endl;
    return res;
}

// v
int FlightManagement::reachableCountriesFromAirport(Vertex<string>* src_airport) {

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

    cout << "You can travel to " << nCountries << " different countries departing from the " << airportMap[src_airport->getInfo()].name << " airport." << endl;
    return nCountries;
}

int FlightManagement::reachableCitiesFromAirport(Vertex<string>* src_airport) {
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

    cout << "You can travel to " << nCities << " different cities departing from the " << airportMap[src_airport->getInfo()].name << " airport." << endl;
    return nCities;

}

int FlightManagement::reachableAirportsFromAirport(Vertex<string>* src_airport) {

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

    cout << "You can travel to " << nAirports << " different airports departing from the " << airportMap[src_airport->getInfo()].name << " airport." << endl;
    return nAirports;
}

// vi
// Number of reachable airports from a given airport with X stops
void FlightManagement::reachableAirportsInXStops(string source, int x) { /**@brief Time complexity:O(V+E) where V and E are the number of vertices and edges,respectively**/
    int res = 0;
    auto v = airNetwork.findVertex(source);
    /*if (v == NULL) {
        cout << "Airport " << source << " doesn't exist" << endl;
        return -1;
    };*/
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
    auto airport = airportMap[source];
    cout << "There are " << res - 1 << " reachable airports with " << x << " stops, from " << airport.name << " (" << airport.code << ") in " << airport.country << endl;
}

// Number of reachable cities from a given airport with X stops
void FlightManagement::reachableCitiesInXStops(string source, int x) {
    std::set<string> res;
    auto v = airNetwork.findVertex(source);
    /*if (v == NULL){
        cout << "Airport " << source << " doesn't exist" << endl;
        return -1;
    }*/
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
    auto airport = airportMap[source];
    cout << "There are " << res.size() - 1 << " reachable cities with " << x << " stops, from " << airport.name << " (" << airport.code << ") in " << airport.country << endl;

}

// Number of reachable countries from a given airport with X stops
void FlightManagement::reachableCountriesInXStops(string source, int x) {
    std::set<string> res;
    auto v = airNetwork.findVertex(source);
    /*if (v == NULL){
        cout << "Airport " << source << " doesn't exist" << endl;
        return -1;
    }*/
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
    auto airport = airportMap[source];
    cout << "There are " << res.size() - 1 << " reachable countries with " << x << " stops, from " << airport.name << " (" << airport.code << ") in " << airport.country << endl;
}
//vii
void FlightManagement::maxTrip() { /**@brief Time complexity: O(V.(V+E)) where V and E are the number of vertices and edges,respectively **/

    // Initialize the result vector to store the longest of the shortest paths.
    std::vector<pair<string, string>> longestShortestPaths;

    int max = 0;

    for (auto source : airNetwork.getVertexSet()) {

        for ( auto source : airNetwork.getVertexSet()) {
            source->setVisited(false);
        }
        // Run BFS from the current source node.
        std::queue<Vertex<string>*> bfsQueue;
        bfsQueue.push(source);
        source->setVisited(true);

        // Data structures to store the current shortest path and its length.
        std::vector<std::string> currentShortestPath;
        int currentShortestPathLength = -1;
        vector<string> furthestDestinations;

        // Process layers in BFS.
        while (!bfsQueue.empty()) {
            int layerSize = bfsQueue.size();
            furthestDestinations.clear();
            for (int i = 0; i < layerSize; ++i) {
                Vertex<string>* currentVertex = bfsQueue.front();
                bfsQueue.pop();
                furthestDestinations.push_back(currentVertex->getInfo());

                for (auto neighborEdge : currentVertex->getAdj()) {
                    Vertex<string>* neighbor = neighborEdge.getDest();


                    if (!neighbor->isVisited()) {
                        bfsQueue.push(neighbor);
                        neighbor->setVisited(true);
                    }
                }

            }

            // Increment the length when starting to visit the next layer.
            ++currentShortestPathLength;
        }

        if (currentShortestPathLength > max) {
            max = currentShortestPathLength;
            longestShortestPaths.clear();
            for (auto i : furthestDestinations) {
                longestShortestPaths.push_back({source->getInfo(), i});

            }

        }
        else if (currentShortestPathLength == max){
            for (auto i : furthestDestinations) {
                longestShortestPaths.push_back({source->getInfo(), i});

            }
        }

    }

    cout << left << setw(50) << "Source:" << setw(50) << "Destination:" << endl;
    for (auto p : longestShortestPaths) {
        cout << left << setw(50) <<  airportMap[p.first].name << setw(50) << airportMap[p.second].name << endl;
    }

    cout << "The maximum trips possible have at most " << max << " stops." << endl;

}
// viii
#include <unordered_map>
#include <queue>



void FlightManagement::topTrafficAirports(int k) { /**@brief Time complexity: O(V + E + k log(N)) where V and E are the number of vertices and edges,respectively and k the given variable**/
    std::unordered_map<std::string, unsigned int> flightsAirport;

    // Priority queue to store the top airports based on traffic
    std::priority_queue<std::pair<unsigned int, std::string>> topAirports;

    for (auto& v : airNetwork.getVertexSet()) {
        std::string source = v->getInfo();

        // Out flights for source
        if (flightsAirport.find(source) != flightsAirport.end()) {
            flightsAirport[source] += v->getAdj().size();
        } else {
            flightsAirport[source] = v->getAdj().size();
        }

        // Incoming flights for dest
        for (auto& f : v->getAdj()) {
            std::string dest = f.getDest()->getInfo();
            if (flightsAirport.find(dest) != flightsAirport.end()) {
                flightsAirport[dest]++;
            } else {
                flightsAirport[dest] = 1;
            }
        }
    }

    // Populate the priority queue with airports and their traffic
    for (const auto& entry : flightsAirport) {
        topAirports.push(std::make_pair(entry.second, entry.first));
    }

    // Print the top k airports with greatest traffic
    std::cout << "Top " << k << " airports with greatest traffic" << std::endl;
    std::cout << std::left << std::setw(43) << "\nAirport:" << std::setw(20) << "Number of Flights:" << std::endl;

    for (int i = 0; i < k && !topAirports.empty(); ++i) {
        auto airport = topAirports.top();
        topAirports.pop();
        std::cout << i+1 << ". " << std::setw(43) << airport.second << std::setw(20) << airport.first << std::endl;
    }
}


// ix - 312
bool inStack(Vertex<string>* w,stack<string> s);
void dfs_art(Graph<string> &g, Vertex<string> *v, stack<string> &s, unordered_set<string> &l, int &i);

void FlightManagement::essentialAirports() {
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
    int count = 1;
    for (auto x : res){
        auto airport = airportMap[x];
        cout << count++ << ". " << airport.name << " (" << airport.code << ") in " << airport.city << ", " << airport.country << endl;
    }
    cout << "There are " << res.size() << " essential airports." << endl;
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
        if(a == w->getInfo()) return true;
        s.pop();
    }
    return false;
}

// 4. Best flight option
bool filter(std::vector<std::pair<string, std::string>> path, int maxAirlines, unordered_set<string> wantedAirlines) {
    // Track unique airlines for each itinerary

    unordered_set<string> airlines;

    // Iterate through flights in the current path starting from the second flight (1st doesn't have an airline associated)
    for (auto flight = path.begin() + 1; flight < path.end(); flight++) {
        // Flag to track if the airline is found in the set of valid airlines
        bool found = false;

        // Insert the airline into the set for uniqueness
        airlines.insert(flight->second);

        // Check if the airline is in the set of valid airlines
        for (const auto &validAirline: wantedAirlines) {
            if (validAirline == flight->second) {
                found = true;
                break;
            }
        }

        // If the first airline in the set is "ignore", do nothing
        if (*wantedAirlines.begin() == "ignore") {
            // Note: Consider adding a comment here to explain why nothing is done
        }
            // If the airline is not found in the set of valid airlines, skip the itinerary
        else if (!found) {
            return false;
        }
    }

    // If the number of unique airlines exceeds the maximum allowed, skip the itinerary
    if (airlines.size() > maxAirlines) {
        return false;
    }
    return true;
    // If the itinerary was not skipped, move to the next itinerary
}

vector<vector<pair<string,string>>> FlightManagement::bestFlightOption(const vector<Vertex<string>*> sourceVector, const vector<Vertex<string>*> targetVector, int maxAirlines, unordered_set<string> wantedAirlines) { /**@brief Time complexity: O(S.T.(V+E)) where V, E, S and T are the number of vertices, edges, source vertices and target vertices, respectively**/

    vector<vector<pair<string,string>>> res;

    for(auto source : sourceVector){
        for (auto target : targetVector){

            for (auto v : airNetwork.getVertexSet()){
                v->setVisited(false);
                v->setProcessing(false);
            }

            std::queue<std::vector<std::pair<std::string, std::string>>> q;

            // Push root element
            q.push({{source->getInfo(), "ignore"}});
            source->setVisited(true);

            while(!q.empty()){
                // Root path
                std::vector<std::pair<string, std::string>> rootPath = q.front();
                q.pop();

                if(!res.empty() && rootPath.size() > res.front().size()){
                    continue;
                }

                auto prev = rootPath.back().first;
                for(auto e : airNetwork.findVertex(prev)->getAdj()){
                    auto w = e.getDest();
                    if(!w->isVisited()){
                        vector<pair<string, string>> childPath = rootPath;
                        childPath.emplace_back(w->getInfo(), e.getAirlineCode());
                        if(w == target){
                            w->setVisited(false);
                            //if((res.empty() || childPath.size() <= res.front().size()) && filter(childPath,maxAirlines,wantedAirlines)){
                            res.push_back(childPath);
                            //}
                            continue;
                        }
                        q.push(childPath);
                    }
                }
                airNetwork.findVertex(prev)->setVisited(true);
            }
        }
    }

    for (auto path = res.begin(); path != res.end();){
        if (!filter(*path,maxAirlines,wantedAirlines)) path = res.erase(path);
        else path++;
    }

    int min = INT_MAX;
    for (auto x : res){
        if (x.size() < min) min = x.size();
    }

    for (auto it = res.begin(); it < res.end();){
        if (it->size() > min) it = res.erase(it);
        else it++;
    }
    return res;
}












