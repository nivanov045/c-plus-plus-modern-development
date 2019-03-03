#include <set>
#include <vector>
//#include <ostream>
//#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border)
{
  auto borderIt = find_if(elements.begin(), elements.end(), [border](const T& el) {return el > border; });
  return vector<T>(borderIt, elements.end());
}

//int main() {
//  for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
//    cout << x << " ";
//  }
//  cout << endl;
//
//  string to_find = "Python";
//  cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
//  system("pause");
//  return 0;
//}