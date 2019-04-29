#include <ostream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

template <typename T> vector<T> Sqr(vector<T> x);
template <typename Key, typename Value> map<Key, Value> Sqr(map<Key, Value> x);
template <typename First, typename Second> pair<First, Second> Sqr(pair<First, Second> x);
template <typename T> T Sqr(T x);

template <typename T>
vector<T> Sqr(vector<T> x) {
  vector<T> result;
  for (const auto& iv : x) {
    result.emplace_back(Sqr(iv));
  }
  return result;
}

template <typename Key, typename Value>
map<Key, Value> Sqr(map<Key, Value> x) {
  map<Key, Value> result;
  for (auto& im : x) {
    result[im.first] = Sqr(im.second);
  }
  return result;
}

template <typename First, typename Second> 
pair<First, Second> Sqr(pair<First, Second> x)
{
  return { Sqr(x.first), Sqr(x.second) };
}

template <typename T> T Sqr(T x)
{
  return x * x;
}

//int main(int argc, char* argv[])
//{
//  vector<int> v = { 1, 2, 3 };
//  cout << "vector:";
//  for (int x : Sqr(v)) {
//    cout << ' ' << x;
//  }
//  cout << endl;
//
//  map<int, pair<int, int>> map_of_pairs = {
//    {4, {2, 2}},
//    {7, {4, 3}}
//  };
//  cout << "map of pairs:" << endl;
//  for (const auto& x : Sqr(map_of_pairs)) {
//    cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
//  }
//  return 0;
//}
