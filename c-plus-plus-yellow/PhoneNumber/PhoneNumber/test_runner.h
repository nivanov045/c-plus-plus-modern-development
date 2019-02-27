#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include "phone_number.h"

using namespace std;

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const std::string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    }
    catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    }
    catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      std::cerr << fail_count << " unit tests failed. Terminate" << endl;
      system("pause");
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

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

void Assert(bool b, const string& hint);

void TestPositiveCase();

void TestNegativeCase();

void TestAll();
