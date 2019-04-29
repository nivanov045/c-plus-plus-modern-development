#include <utility>
#include <algorithm>
#include <ostream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix)
{
  string prefString = { prefix };
  return equal_range(range_begin, range_end, prefString, [](const string it1, const string it2)
  {
    return it1[0] < it2[0];
  });
}

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const string& prefix)
{
  return equal_range(range_begin, range_end, prefix, [&prefix](const string it1, const string it2)
  {
    return it1.substr(0, prefix.length()) < it2.substr(0, prefix.length());
  });
}


int main() {
  const vector<string> sorted_strings = { "moscow", "motovilikha", "murmansk" };

  const auto mo_result =
    FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
  for (auto it = mo_result.first; it != mo_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;

  const auto mt_result =
    FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
  cout << (mt_result.first - begin(sorted_strings)) << " " <<
    (mt_result.second - begin(sorted_strings)) << endl;

  const auto na_result =
    FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
  cout << (na_result.first - begin(sorted_strings)) << " " <<
    (na_result.second - begin(sorted_strings)) << endl;
  system("pause");
  return 0;
}