#include "test_runner.h"

#include <ostream>
using namespace std;

#define PRINT_VALUES(out, x, y) out << (x) << endl << (y) << endl

int main() {
  TestRunner tr;
  tr.RunTest([] {
    ostringstream output;
    PRINT_VALUES(output, 5, "red belt");
    ASSERT_EQUAL(output.str(), "5\nred belt\n");
    ostringstream output2;
    if (true)
      PRINT_VALUES(output2, 5, "red belt");
    ASSERT_EQUAL(output2.str(), "5\nred belt\n");
    ostringstream output3;
    if (false)
      PRINT_VALUES(output3, 5, "red belt");
    else 
      PRINT_VALUES(output3, 5, "white belt");
    ASSERT_EQUAL(output3.str(), "5\nwhite belt\n");
  }, "PRINT_VALUES usage example");
}
