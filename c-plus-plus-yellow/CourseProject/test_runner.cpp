#include "test_runner.h"

void TestPositiveCase()
{
}

void TestNegativeCase()
{
}

ostream & operator<<(iostream & stream, const vector<string>& vect)
{
  for (const auto& v : vect)
    cout << v << " ";
  return stream;
}

ostream& operator<<(iostream& stream, vector<string> vect)
{
  for (const auto& v : vect)
    cout << v << " ";
  return stream;
}

void Assert(bool b, const string& hint)
{
  AssertEqual(b, true, hint);
}
