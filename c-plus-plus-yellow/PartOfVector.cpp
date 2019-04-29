#include <vector>
#include <ostream>
#include <iostream>
#include <algorithm>

using namespace std;

void PrintVectorPart(const vector<int>& numbers)
{
  auto border = find_if(numbers.begin(), numbers.end(), [](int num) {return num < 0; });
  if (border == numbers.begin())
    return;
  if (border == numbers.end())
    for (auto it = numbers.rbegin(); it < numbers.rend(); ++it)
      cout << *it << " ";
  else {
    auto it = border;
    while (it != numbers.begin()) {
      --it;
      cout << *it << " ";
    }
  }
}

//int main() {
//  PrintVectorPart({ 6, 1, 8, -5, 4 });
//  cout << endl;
//  PrintVectorPart({ -6, 1, 8, -5, 4 });  // ничего не выведется
//  cout << endl;
//  PrintVectorPart({ 6, 1, 8, 5, 4 });
//  cout << endl;
//  system("pause");
//  return 0;
//}