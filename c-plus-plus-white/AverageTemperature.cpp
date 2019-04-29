#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
  int N;
  std::cin >> N;
  std::vector<int> temperatures;
  int sum = 0;
  for (auto i = 0; i < N; ++i) {
    int tmp;
    std::cin >> tmp;
    temperatures.emplace_back(tmp);
    sum += tmp;
  }
  std::vector<int> result;
  for (auto v = 0; v < temperatures.size(); ++v) {
    if (temperatures.at(v) > sum / N)
      result.push_back(v);
  }
  std::cout << result.size() << std::endl;
  for (const auto& v : result)
    std::cout << v << " ";
  /*system("pause");*/
  return 0;
}
