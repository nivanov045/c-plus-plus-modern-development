#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

bool IsPalindrom(const string& str) {
  // Вы можете вставлять сюда различные реализации функции,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный
}

void TestPositiveCase()
{
  AssertEqual(IsPalindrom(""), true, "Empty");
  AssertEqual(IsPalindrom("q"), true, "One");
  AssertEqual(IsPalindrom("qwewq"), true, "Normal");
  AssertEqual(IsPalindrom(" qwewq "), true, "Normal with space");
}

void TestNegativeCase()
{
  AssertEqual(IsPalindrom("12"), false, "12");
  AssertEqual(IsPalindrom("121 "), false, "121 ");
  AssertEqual(IsPalindrom("qwe23ewq"), false, "qwe23ewq");
  AssertEqual(IsPalindrom(" q w ewq "), false, " q w ewq ");
  AssertEqual(IsPalindrom("q wert yuytrewq"), false, "rose");
  AssertEqual(IsPalindrom("baobab"), false, "baobab");
  AssertEqual(IsPalindrom(" qwewq"), false, " qwewq");
  AssertEqual(IsPalindrom("1qwewq"), false, "1qwewq");
  AssertEqual(IsPalindrom("qwewq2"), false, "qwewq2");
  //tests from forum
  AssertEqual(IsPalindrom("olol"), 0);
  AssertEqual(IsPalindrom("motor"), 0);
  AssertEqual(IsPalindrom("topo gun"), 0);
  AssertEqual(IsPalindrom("olol "), 0);
  AssertEqual(IsPalindrom(" lol"), 0);
  AssertEqual(IsPalindrom("olo" + '\n'), 0);
}

void TestAll()
{
  TestRunner runner;
  runner.RunTest(TestPositiveCase, "TestPositiveCase");
  runner.RunTest(TestNegativeCase, "TestNegativeCase");
}

int main() {
  TestRunner runner;
  TestAll();
  return 0;
}
