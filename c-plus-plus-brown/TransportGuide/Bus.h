#pragma once
#include <utility>
#include <vector>
#include <algorithm>

#include "Route.h"



class Bus
{
public:
  Bus(std::string iName, Route iRoute) : _name(std::move(iName)), _route(std::move(iRoute)) {}
  std::string  GetName() const { return _name; }
  int GetNumberOfStops() const { return _route.GetNumberOfStops(); }
  int GetNumberOfUniqueStops() const { return _route.GetNumberOfUniqueStops(); }
  double GetRouteLength() const
  {
    return _route.GetLength();
  }
private:
  std::string _name;
  Route _route;
};
