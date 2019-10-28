#pragma once

#include <utility>

struct Coordinates
{
  double latitude;
  double longitude;
};

class Stop {
public:
  Stop(std::string iName, double iLatitude, double iLongitude) : _name(std::move(iName)),
                                                                 _coordinates({ iLatitude, iLongitude }) {}
  std::string  GetName() const { return _name; }
  Coordinates  GetCoordinates() const { return _coordinates; }
  
private:
  std::string _name;
  Coordinates _coordinates;
};