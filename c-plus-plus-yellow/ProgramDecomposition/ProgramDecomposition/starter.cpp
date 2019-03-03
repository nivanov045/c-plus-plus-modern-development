#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include "responses.h"

using namespace std;

















class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& iStops) {
    for (const string& stop : iStops)
      buses_to_stops[bus].push_back(stop);
    for (const string& stop : iStops)
      stops_to_buses[stop].push_back(bus);
    /*vector<string>& stops = buses_to_stops[bus];
    stops.resize(iStops.size());
    for (string& stop : stops) {
      stop = 
      stops_to_buses[stop].push_back(bus);
    }*/
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    if (stops_to_buses.count(stop) == 0)
      return { false, {} };
    BusesForStopResponse result;
    result.stopExist = true;
    for (const string& bus : stops_to_buses.at(stop))
      result.buses.emplace_back(bus);
    return result;
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
    if (buses_to_stops.count(bus) == 0)
      return { false };
    StopsForBusResponse result;
    result.busExist = true;
    result.stopsForBus = buses_to_stops.at(bus);
    result.stops_to_buses = stops_to_buses;
    result.bus = bus;
    return result;
  }

  AllBusesResponse GetAllBuses() const {
    return { buses_to_stops };
  }
private:
  map<string, vector<string>> buses_to_stops, stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
