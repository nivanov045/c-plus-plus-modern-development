#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

ostream& operator<<(ostream& stream, vector<int> vect)
{
  for (const auto v : vect) {
    stream << v << ' ';
  }
  stream << endl;
  return stream;
}

int main(int argc, char* argv[])
{
  int N;
  cin >> N;
  vector<int> numbers;
  for (int i = N; i > 0; i--)
    numbers.emplace_back(i);
  do {
    std::cout << numbers;
  } while (std::prev_permutation(numbers.begin(), numbers.end()));
  /*system("pause");*/
  return 0;
}
