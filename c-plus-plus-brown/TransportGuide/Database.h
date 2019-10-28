#pragma once

#include "Bus.h"

#include <set>
#include <algorithm>
#include <unordered_set>
#include <iostream>
#include <string>

class Database
{
public:
  void AddStop(const std::string& iName, double iLatitude, double iLongitude)
  {
    _stops.emplace_back(iName, iLatitude, iLongitude);
  }
  void AddBus(const std::string& iName, const std::vector<std::string>& iStopsNames, bool iIsCyclic)
  {
    std::vector<std::shared_ptr<Stop>> route;
    for (const auto& name : iStopsNames) {
      auto stop = *std::find_if(_stops.begin(), _stops.end(), [name](const Stop& iStop)
      {
        return iStop.GetName() == name;
      });
      route.push_back(std::make_shared<Stop>(stop));
    }
    if (!iIsCyclic) {
      for (auto routeStopIt = ++route.rbegin(); routeStopIt != route.rend(); ++routeStopIt) {
        route.push_back(*routeStopIt);
      }
    }
    _buses.emplace_back(iName, route);
  }
  void PrintBusInfo(const std::string& iName) const
  {
    const auto& bus = *std::find_if(_buses.begin(), _buses.end(), [iName](const Bus& iBus)
    {
      return iBus.GetName() == iName;
    });
    std::cout << "Bus " << bus.GetName() << ": " << bus.GetNumberOfStops() << " stops on route, " <<
      bus.GetNumberOfUniqueStops() << " unique stops, " << bus.GetRouteLength() << " route length" << std::endl;       
  }
private:
  std::vector<Bus> _buses;
  std::vector<Stop> _stops;
};
