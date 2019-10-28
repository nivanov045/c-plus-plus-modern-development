#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

enum class Gender {
  FEMALE,
  MALE
};

struct Person {
  int age;
  Gender gender;
  bool is_employed;
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
  if (range_begin == range_end) {
    return 0;
  }
  vector<typename InputIt::value_type> range_copy(range_begin, range_end);
  auto middle = begin(range_copy) + range_copy.size() / 2;
  nth_element(
    begin(range_copy), middle, end(range_copy),
    [](const Person& lhs, const Person& rhs) {
      return lhs.age < rhs.age;
    }
  );
  return middle->age;
}

void PrintStats(vector<Person> persons)
{
  cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << endl;
  auto print = [&](const string& iCategory, int age)
  {
    cout << "Median age for " + iCategory + " = " << age << endl;

  };

  auto isFemale = [](const Person& iPerson) { return iPerson.gender == Gender::FEMALE; };
  auto isMale = [](const Person& iPerson) { return iPerson.gender == Gender::MALE; };
  auto isEmployed = [](const Person& iPerson) { return iPerson.is_employed; };
  auto isUnemployed = [](const Person& iPerson) { return !iPerson.is_employed; };
  auto lastIt = partition(persons.begin(), persons.end(), isFemale);
  print("females", ComputeMedianAge(persons.begin(), lastIt));
  lastIt = partition(persons.begin(), persons.end(), isMale);
  print("males", ComputeMedianAge(persons.begin(), lastIt));
  lastIt = partition(persons.begin(), persons.end(), [&](const Person& iPerson)
  {
    return isFemale(iPerson) && isEmployed(iPerson);
  });
  print("employed females", ComputeMedianAge(persons.begin(), lastIt));
  lastIt = partition(persons.begin(), persons.end(), [&](const Person& iPerson)
    {
      return isFemale(iPerson) && isUnemployed(iPerson);
    });
  print("unemployed females", ComputeMedianAge(persons.begin(), lastIt));
  lastIt = partition(persons.begin(), persons.end(), [&](const Person& iPerson)
    {
      return isMale(iPerson) && isEmployed(iPerson);
    });
  print("employed males", ComputeMedianAge(persons.begin(), lastIt));
  lastIt = partition(persons.begin(), persons.end(), [&](const Person& iPerson)
    {
      return isMale(iPerson) && isUnemployed(iPerson);
    });
  print("unemployed males", ComputeMedianAge(persons.begin(), lastIt));
}

int main() {
  vector<Person> persons = {
      {31, Gender::MALE, false},
      {40, Gender::FEMALE, true},
      {24, Gender::MALE, true},
      {20, Gender::FEMALE, true},
      {80, Gender::FEMALE, false},
      {78, Gender::MALE, false},
      {10, Gender::FEMALE, false},
      {55, Gender::MALE, true},
  };
  PrintStats(persons);
  system("pause");
  return 0;
}
