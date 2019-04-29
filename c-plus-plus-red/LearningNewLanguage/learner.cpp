#include <algorithm>
#include <string>
#include <vector>
#include "profile.h"
#include <set>

using namespace std;

class Learner {
 private:
  set<string> dict;

 public:
  int Learn(const vector<string>& words) {
    LOG_DURATION("Learn: ");
    int newWords = 0;
    for (const auto& word : words) {
      if (dict.emplace(word).second) {
        ++newWords;
        //dict.push_back(word);
      }
    }
    return newWords;
  }

  vector<string> KnownWords() {
    LOG_DURATION("KnownWords: ");
    //sort(dict.begin(), dict.end());
    //dict.erase(unique(dict.begin(), dict.end()), dict.end());
    return vector<string>(dict.begin(), dict.end());
  }
};
