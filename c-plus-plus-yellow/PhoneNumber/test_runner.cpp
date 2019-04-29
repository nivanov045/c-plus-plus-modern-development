#include "test_runner.h"

void Assert(bool b, const string& hint)
{
  AssertEqual(b, true, hint);
}

void TestPositiveCase()
{
  PhoneNumber num("+7-495-111-22-33");
  AssertEqual(num.GetCountryCode(), "7", "GetCountryCode");
  AssertEqual(num.GetCityCode(), "495", "GetCityCode");
  AssertEqual(num.GetLocalNumber(), "111-22-33", "GetLocalNumber");
  AssertEqual(num.GetInternationalNumber(), "+7-495-111-22-33", "GetInternationalNumber");
}

void TestNegativeCase()
{
}

void TestAll()
{
  TestRunner runner;
  runner.RunTest(TestPositiveCase, "TestPositiveCase");
  runner.RunTest(TestNegativeCase, "TestNegativeCase");
}
