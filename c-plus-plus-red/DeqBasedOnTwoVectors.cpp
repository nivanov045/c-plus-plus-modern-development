//#include "test_runner.h"

#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class Deque
{
public:
  Deque() = default;
  bool Empty() const { return Size() == 0; }
  size_t Size() const { return _front.size() + _back.size(); }
  T& operator[](size_t index)
  {
    if (index < _front.size())
      return _front[_front.size() - 1 - index];
    return _back[index - _front.size()];
  }
  const T& operator[](size_t index) const 
  {
    if (index < _front.size())
      return _front[_front.size() - 1 - index];
    return _back[index - _front.size()];
  }

  T& At(size_t index)
  {
    if (index >= Size() || index < 0)
      throw out_of_range("Index is out of range!");
    return operator[](index);
  }
  const T& At(size_t index) const
  {
    if (index >= Size() || index < 0)
      throw out_of_range("Index is out of range!");
    return operator[](index);
  }

  T& Front()
  {
    if (!_front.empty())
      return _front.back();
    return _back.front();
  }
  const T& Front() const
  {
    if (!_front.empty())
      return _front.back();
    return _back.front();
  }
  T& Back()
  {
    if (!_back.empty())
      return _back.back();
    return _front.front();
  }
  const T& Back() const { return _back.back(); }

  void PushFront(const T& el) { _front.emplace_back(el); }
  void PushBack(const T& el) { _back.emplace_back(el); }

  private:
  vector<T> _front;
  vector<T> _back;
};

//void TestDeque() {
//  Deque<double> d;
//  ASSERT_EQUAL(d.Size(), 0u);
//  d.PushBack(1.0);
//  d.Front();
//  d.Back();
//  ASSERT_EQUAL(d.Size(), 1u);
//  ASSERT_EQUAL(d.Empty(), false);
//  ASSERT_EQUAL(d.At(0), 1.0);
//  ASSERT_EQUAL(d[0], 1.0);
//  d.PushFront(-1.0);
//  ASSERT_EQUAL(d.Size(), 2u);
//  ASSERT_EQUAL(d.At(0), -1.0);
//  ASSERT_EQUAL(d[0], -1.0);
//  ASSERT_EQUAL(d.At(1), 1.0);
//  ASSERT_EQUAL(d[1], 1.0);
//  d[1] = 2.0;
//  ASSERT_EQUAL(d.At(1), 2.0);
//  ASSERT_EQUAL(d.Front(), -1.0);
//  ASSERT_EQUAL(d.Back(), 2.0);
//}
//
//int main() {
//  TestRunner tr;
//  RUN_TEST(tr, TestDeque);
//  return 0;
//}