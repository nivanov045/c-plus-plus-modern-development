#include <ostream>
#include <iostream>
#include <map>
#include <string>

using namespace std;

template <typename Key, typename Value> Value& GetRefStrict(map<Key, Value>& iMap, Key iKey)
{
  if (!iMap.count(iKey))
    throw runtime_error("Key not found!");
  return iMap.at(iKey);
}
//
//int main(int argc, char* argv[])
//{
//  map<int, string> m = { {0, "value"} };
//  string& item = GetRefStrict(m, 0);
//  item = "newvalue";
//  cout << m[0] << endl;
//}
