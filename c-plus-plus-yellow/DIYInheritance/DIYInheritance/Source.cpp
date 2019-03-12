#include <iostream>
#include <string>

using namespace std;

class Animal {
public:
  Animal(const string iName) : Name(iName) {}

  const string Name;
};


class Dog : public Animal {
public:
  Dog(const string iName) : Animal(iName) {}

  void Bark() {
    cout << Name << " barks: woof!" << endl;
  }
};
