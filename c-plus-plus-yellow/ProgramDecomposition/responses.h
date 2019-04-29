#pragma once
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <cassert>


using namespace std;

struct BusesForStopResponse {
  bool stopExist;
  std::vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
  bool busExist;
  vector<string> stopsForBus;
  map<string, vector<string>> stops_to_buses;
  string bus;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
  map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r);