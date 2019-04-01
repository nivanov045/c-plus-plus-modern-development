#include "test_runner.h"

using namespace std;

template <typename T>
class Table
{
public:
  Table(size_t iNumOfR, size_t iNumOfC) : _numOfR(iNumOfR), _numOfC(iNumOfC)
  {
    Resize(iNumOfR, iNumOfC);
  }
  void Resize(size_t iNumOfR, size_t iNumOfC)
  {
    _cells.resize(iNumOfR);
    _numOfR = iNumOfR;
    for (auto& r : _cells)
      r.resize(iNumOfC);
    _numOfC = iNumOfC;
  }
  pair<size_t, size_t> Size() const
  {
    return { _numOfR, _numOfC };
  }
  vector<T> operator[](size_t i) const
  {
    return _cells[i];
  }
  vector<T>& operator[](size_t i)
  {
    return _cells[i];
  }
private:
  size_t _numOfR;
  size_t _numOfC;
  vector<vector<T>> _cells;
};

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}