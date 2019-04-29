#include <cstdint>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

//enum class Lang {
//  DE, FR, IT
//};
//
//struct Region {
//  string std_name;
//  string parent_std_name;
//  map<Lang, string> names;
//  int64_t population;
//};

bool operator==(const Region& lhs, const Region& rhs)
{
  return lhs.std_name == rhs.std_name && lhs.parent_std_name == rhs.parent_std_name && lhs.names == rhs.names &&
    lhs.population == rhs.population;
}

int FindMaxRepetitionCount(const vector<Region>& regions)
{
  if (regions.empty())
    return 0;
  int result = 1;
  vector<Region> viewedRegions;
  for (auto r = regions.begin(); r != regions.end(); r++) {
    if (std::find(viewedRegions.begin(), viewedRegions.end(), *r) != viewedRegions.end())
      continue;
    viewedRegions.emplace_back(*r);
    int tmp = count(r, regions.end(), *r);
    if (tmp > result)
      swap(result, tmp);
  }
  return result;
}

//int main() {
//  cout << FindMaxRepetitionCount({
//      {
//          "Moscow",
//          "Russia",
//          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
//          89
//      }, {
//          "Russia",
//          "Eurasia",
//          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
//          89
//      }, {
//          "Moscow",
//          "Russia",
//          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
//          89
//      }, {
//          "Moscow",
//          "Russia",
//          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
//          89
//      }, {
//          "Russia",
//          "Eurasia",
//          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
//          89
//      },
//    }) << endl;
//
//  cout << FindMaxRepetitionCount({
//      {
//          "Moscow",
//          "Russia",
//          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
//          89
//      }, {
//          "Russia",
//          "Eurasia",
//          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
//          89
//      }, {
//          "Moscow",
//          "Russia",
//          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
//          89
//      }, {
//          "Moscow",
//          "Toulouse",
//          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
//          89
//      }, {
//          "Moscow",
//          "Russia",
//          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
//          31
//      },
//    }) << endl;
//
//  return 0;
//}
