#include <vector>
void Reverse(std::vector<int>& v)
{
  std::vector<int> sol;
  for (auto i = v.rbegin(); i != v.rend(); i++)
    sol.emplace_back(*i);
  v.clear();
  for (auto i = sol.begin(); i != sol.end(); i++)
    v.emplace_back(*i);
}

std::vector<int> Reversed(const std::vector<int>& v)
{
  std::vector<int> sol;
  for (auto i = v.rbegin(); i != v.rend(); i++)
    sol.emplace_back(*i);
  return sol;
}

//int main()
//{
//  std::vector<int> numbers = { 1, 5, 3, 4, 2 };
//  std::vector<int> numbers2 = Reversed(numbers);
//  system("pause");
//  return 0;
//}
