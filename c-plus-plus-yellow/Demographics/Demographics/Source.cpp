#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

//enum class Gender {
//  FEMALE,
//  MALE
//};
//
//struct Person {
//  int age;  // возраст
//  Gender gender;  // пол
//  bool is_employed;  // имеет ли работу
//};
//
//// Это пример функции, его не нужно отправлять вместе с функцией PrintStats
//template <typename InputIt>
//int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
//  if (range_begin == range_end) {
//    return 0;
//  }
//  vector<typename InputIt::value_type> range_copy(range_begin, range_end);
//  auto middle = begin(range_copy) + range_copy.size() / 2;
//  nth_element(
//    begin(range_copy), middle, end(range_copy),
//    [](const Person& lhs, const Person& rhs) {
//    return lhs.age < rhs.age;
//  }
//  );
//  return middle->age;
//}

void PrintStats(vector<Person> persons)
{
  cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << endl;
  const auto femIt = partition(persons.begin(), persons.end(), [](Person p) {return p.gender == Gender::MALE; });
  //Male/Female
  cout << "Median age for females = " << ComputeMedianAge(femIt, persons.end()) << endl;
  cout << "Median age for males = " << ComputeMedianAge(persons.begin(), femIt) << endl;
  const auto emplFemIt = partition(femIt, persons.end(), [](Person p) {return !p.is_employed; });
  //Male/unempl Fem/ empl fem/
  cout << "Median age for employed females = " << ComputeMedianAge(emplFemIt, persons.end()) << endl;
  cout << "Median age for unemployed females = " << ComputeMedianAge(femIt, emplFemIt) << endl;
  const auto emplMalIt = partition(persons.begin(), femIt, [](Person p) {return !p.is_employed; });
  //unempl mal/ empl mal/unempl Fem/ empl fem/
  cout << "Median age for employed males = " << ComputeMedianAge(emplMalIt, femIt) << endl;
  cout << "Median age for unemployed males = " << ComputeMedianAge(persons.begin(), emplMalIt) << endl;
}

//int main() {
//  vector<Person> persons = {
//      {31, Gender::MALE, false},
//      {40, Gender::FEMALE, true},
//      {24, Gender::MALE, true},
//      {20, Gender::FEMALE, true},
//      {80, Gender::FEMALE, false},
//      {78, Gender::MALE, false},
//      {10, Gender::FEMALE, false},
//      {55, Gender::MALE, true},
//  };
//  PrintStats(persons);
//  system("pause");
//  return 0;
//}
