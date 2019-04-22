#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
  int range_length = range_end - range_begin;
  if (range_length < 2) {
    return;
  }

  vector<typename RandomIt::value_type> elements(make_move_iterator(range_begin), make_move_iterator(range_end));

  auto one_third = elements.begin() + range_length / 3;
  auto two_third = elements.begin() + range_length * 2 / 3;

  MergeSort(elements.begin(), one_third);
  MergeSort(one_third, two_third);
  MergeSort(two_third, elements.end());

  vector<typename RandomIt::value_type> interim_result;
  merge(make_move_iterator(elements.begin()), make_move_iterator(one_third), make_move_iterator(one_third),
        make_move_iterator(two_third),
        back_inserter(interim_result));

  merge(make_move_iterator(interim_result.begin()), make_move_iterator(interim_result.end()),
        make_move_iterator(two_third), make_move_iterator(elements.end()),
        range_begin);
}

void TestIntVector()
{
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main()
{
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
