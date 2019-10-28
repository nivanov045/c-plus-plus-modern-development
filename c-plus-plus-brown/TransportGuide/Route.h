#pragma once
#include "Stop.h"
#include <vector>
#include <memory>

static const double PI = 3.1415926535;
static const double EarthRadius = 6371000;
inline void toRad(double& ioInGrad) { ioInGrad *= (PI / 180.0); }

inline double CalculateLenght(Coordinates lhs, Coordinates rhs)
{
  toRad(lhs.latitude);
  toRad(lhs.longitude);
  toRad(rhs.latitude);
  toRad(rhs.longitude);
  return acos(sin(lhs.latitude) * sin(rhs.latitude) + cos(lhs.latitude) * cos(rhs.latitude) *
    cos(abs(lhs.longitude- rhs.longitude))) * EarthRadius;
}

class Route
{
public:
  Route(std::vector<std::shared_ptr<Stop>>& iRoute) : _route(iRoute) {}
  double GetLength() const
  {
    double result = 0.0;
    for (auto it = ++_route.begin(); it != _route.end(); ++it) {
      result += CalculateLenght(it->get()->GetCoordinates(), (++it)->get()->GetCoordinates());
      --it;
    }
    return result;
  }
  int GetNumberOfStops() const { return _route.size(); }
  int GetNumberOfUniqueStops() const
  {
    auto routeCopy = _route;
    std::sort(routeCopy.begin(), routeCopy.end());
    auto uniqIt = std::unique(routeCopy.begin(), routeCopy.end());
    return uniqIt - routeCopy.begin();
  }

private:
  const std::vector<std::shared_ptr<Stop>> _route;
};