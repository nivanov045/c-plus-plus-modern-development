#include <ostream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//template <typename RandomIt>
//void MergeSort(RandomIt range_begin, RandomIt range_end)
////Implementation with splitting into 2 parts 
//{
//  if (range_end - range_begin < 2)
//    return;
//  vector<typename RandomIt::value_type> elements(range_begin, range_end);
//  MergeSort(elements.begin(), elements.begin() + elements.size() / 2);
//  MergeSort(elements.begin() + elements.size() / 2, elements.end());
//  merge(elements.begin(), elements.begin() + elements.size() / 2, elements.begin() + elements.size() / 2, elements.end(), range_begin);
//}

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
//Implementation with splitting into 3 parts 
{
  if (range_end - range_begin < 2)
    return;
  vector<typename RandomIt::value_type> elements(range_begin, range_end);
  MergeSort(elements.begin(), elements.begin() + elements.size() / 3);
  MergeSort(elements.begin() + elements.size() / 3, elements.begin() + elements.size() * 2 / 3);
  MergeSort(elements.begin() + elements.size() * 2 / 3, elements.end());
  vector<typename RandomIt::value_type> tmp;
  merge(elements.begin(), elements.begin() + elements.size() / 3,
                                 elements.begin() + elements.size() / 3, elements.begin() + elements.size() * 2 / 3,
                                 back_inserter(tmp));
  merge(tmp.begin(), tmp.end(),
    elements.begin() + elements.size() * 2 / 3, elements.end(),
    range_begin);
}

//int main() {
//  vector<int> v = { 6, 4, 7, 6, 4, 4, 0, 1 };
//  MergeSort(begin(v), end(v));
//  for (int x : v) {
//    cout << x << " ";
//  }
//  cout << endl;
//  system("pause");
//  return 0;
//}