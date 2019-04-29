#include "bus_manager.h"

void BusManager::AddBus(const string& bus, const vector<string>& iStops) {
  for (const string& stop : iStops)
    buses_to_stops[bus].push_back(stop);
  for (const string& stop : iStops)
    stops_to_buses[stop].push_back(bus);
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
  if (stops_to_buses.count(stop) == 0)
    return { false, {} };
  BusesForStopResponse result;
  result.stopExist = true;
  for (const string& bus : stops_to_buses.at(stop))
    result.buses.emplace_back(bus);
  return result;
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
  if (buses_to_stops.count(bus) == 0)
    return { false };
  StopsForBusResponse result;
  result.busExist = true;
  result.stopsForBus = buses_to_stops.at(bus);
  result.stops_to_buses = stops_to_buses;
  result.bus = bus;
  return result;
}

AllBusesResponse BusManager::GetAllBuses() const {
  return { buses_to_stops };
}