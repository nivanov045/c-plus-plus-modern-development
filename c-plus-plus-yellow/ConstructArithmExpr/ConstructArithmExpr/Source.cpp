#include <iostream>
#include <string>
#include <deque>

using namespace std;

int main(int argc, char* argv[])
{
  int x;
  int N;
  cin >> x >> N;
  deque<string> result;
  result.emplace_back(to_string(x));
  string end;
  getline(cin, end);
  int prevPrior = 1; //0 - +-, 1 - */
  for (int i = 0; i < N; ++i) {
    //cout << i << endl;
    string operation;
    getline(cin, operation);
    //cout << operation[0] << endl;
    int curPrior = (operation[0] == '+' || operation[0] == '-') ? 0 : 1;
    if (prevPrior < curPrior) {
      result.emplace_front("(");
      result.emplace_back(")");
    }
    result.emplace_back(" " + operation);
    prevPrior = curPrior;
  }
  for (auto it : result)
    cout << it;
  cout << endl;
  //system("pause");
  return 0;
}
