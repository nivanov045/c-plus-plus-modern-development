#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main(int argc, char* argv[])
{
  int Q;
  std::cin >> Q;
  std::vector<double> queue;
  for (auto i = 0; i < Q; i++) {
    std::string command;
    std::cin >> command;
    if (command == "WORRY_COUNT") {
      std::cout << count(queue.begin(), queue.end(), 1) << std::endl;
      continue;
    }
    int param = 0;
    std::cin >> param;
    if (command == "WORRY") {
      queue.at(param) = 1;
    } 
    else if (command == "QUIET") {
      queue.at(param) = 0;
    } 
    else if (command == "COME") {
      queue.resize(queue.size() + param, 0);
    }
  }
  system("pause");
  return 0;
}
