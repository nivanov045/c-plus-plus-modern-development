#include <ostream>
#include <iomanip>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <memory>

using namespace std;

class Figure
{
public:
  virtual string Name() = 0;
  virtual double Perimeter() = 0;
  virtual double Area() = 0;
};

class Triangle : public Figure
{
public:
  Triangle(double a, double b, double c) : _a(a), _b(b), _c(c) {}
  string Name() override
  {
    return "TRIANGLE";
  }
  double Perimeter() override
  {
    return _a + _b + _c;
  }
  double Area() override
  {
    const double halfPerim = Perimeter() / 2;
    return sqrt(halfPerim * (halfPerim - _a) * (halfPerim - _b) * (halfPerim - _c));
  }
private:
  double _a;
  double _b;
  double _c;
};

class Rect : public Figure
{
public:
  Rect(double w, double h) : _w(w), _h(h) {}
  string Name() override
  {
    return "RECT";
  }
  double Perimeter() override
  {
    return 2 * (_w + _h);
  }
  double Area() override
  {
    return _w * _h;
  }
private:
  double _w;
  double _h;
};

class Circle: public Figure
{
public:
  Circle(double r) : _r(r) {}
  string Name() override
  {
    return "CIRCLE";
  }
  double Perimeter() override
  {
    return 2 * 3.14 * _r;
  }
  double Area() override
  {
    return 3.14 * _r * _r;
  }
private:
  double _r;
};

shared_ptr<Figure> CreateFigure(istream& stream)
{
  string figType;
  stream >> figType;
  shared_ptr<Figure> result;
  if (figType == "TRIANGLE") {
    double a, b, c;
    stream >> a >> b >> c;
    result = make_shared<Triangle>(a, b, c);
  }
  if (figType == "RECT") {
    double w, h;
    stream >> w >> h;
    result = make_shared<Rect>(w, h);
  }
  if (figType == "CIRCLE") {
    double r;
    stream >> r;
    result = make_shared<Circle>(r);
  }
  return result;
}

int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      figures.push_back(CreateFigure(is));
    }
    else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
          << current_figure->Name() << " "
          << current_figure->Perimeter() << " "
          << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}
