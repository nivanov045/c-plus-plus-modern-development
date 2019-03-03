#include <string>
#include <vector>
#include <algorithm>
//#include <iostream>

using namespace std;

vector<string> SplitIntoWords(const string& s)
{
  vector<string> result;
  auto spaceIteratorFirst = s.begin();
  auto spaceIteratorSecond = s.begin();
  for (;;) {
    spaceIteratorFirst = spaceIteratorSecond;
    spaceIteratorSecond = find(spaceIteratorFirst, s.end(), ' ');
    result.emplace_back(spaceIteratorFirst, spaceIteratorSecond);
    if (spaceIteratorSecond == s.end())
      break;
    ++spaceIteratorSecond;
  }
  return result;
}

//int main() {
//  string s = "C Cpp Java Python";
//
//  vector<string> words = SplitIntoWords(s);
//  cout << words.size() << " ";
//  for (auto it = begin(words); it != end(words); ++it) {
//    if (it != begin(words)) {
//      cout << "/";
//    }
//    cout << *it;
//  }
//  cout << endl;
//  system("pause");
//  return 0;
//}