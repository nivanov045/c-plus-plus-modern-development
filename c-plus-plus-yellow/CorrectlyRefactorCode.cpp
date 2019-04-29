#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:

  Person(const string& name) : Name(name) {}

  virtual void Walk(const string& destination) const
  {
    DescribeActivity("walks to: " + destination);
  }

  string GetProfession() const
  {
    return Profession;
  }
  
  string GetName() const
  {
    return Name;
  }
protected:
  string Name;
  string Profession;

  void DescribeActivity(const string& activity) const
  {
    cout << Profession << ": " << Name << " " << activity << endl;
  }
};

class Student : public Person {
public:

  Student(const string& name, const string& favouriteSong) : Person(name), FavouriteSong(favouriteSong)
  {
    Profession = "Student";
  }

  void Learn() const
  {
    DescribeActivity("learns");
  }

  void Walk(const string& destination) const override
  {
    Person::Walk(destination);
    SingSong();
  }

  void SingSong() const
  {
    DescribeActivity("sings a song: " + FavouriteSong);
  }

private:
  string FavouriteSong;
};


class Teacher : public Person {
public:

  Teacher(const string& name, const string& subject) : Person(name), Subject(subject)
  {
    Profession = "Teacher";
  }

  void Teach() const {
    DescribeActivity("teaches: " + Subject);
  }

private:
  string Subject;
};


class Policeman : public Person{
public:
  Policeman(const string& name) : Person(name)
  {
    Profession = "Policeman";
  }

  void Check(const Person& p) const
  {
    DescribeActivity("checks " + p.GetProfession() + ". " + p.GetProfession() + "'s name is: " + p.GetName());
  }
};

void VisitPlaces(const Person& pers, const vector<string>& places)
{
  for (auto p : places) {
    pers.Walk(p);
  }
}

int main() {
  Teacher t("Jim", "Math");
  Student s("Ann", "We will rock you");
  Policeman p("Bob");

  VisitPlaces(t, { "Moscow", "London" });
  p.Check(s);
  VisitPlaces(s, { "Moscow", "London" });
  
  //Little bit more tests
  p.Check(t);
  p.Check(p);
  return 0;
}
