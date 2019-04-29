#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
  int Q = 0;
  std::cin >> Q;
  std::vector<std::vector<std::string>> tasks;
  int month = 1;
  int days = 31;
  tasks.resize(days);
  for (int i = 0; i < Q; i++) {
    std::string command;
    std::cin >> command;
    if (command == "ADD") {
      int d;
      std::string s;
      std::cin >> d >> s;
	  tasks.at(d - 1).emplace_back(s);
    }
    else if (command == "NEXT") { 
      if (month != 12)
        month++;
      else
        month = 1;
	  int prevDays = days;
      switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
			days = 31;
			break;
		case 2:
			days = 28;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			days = 30;
			break;
	  };
	  if (days < prevDays) {
		  for (auto d = days + 1 - 1; d <= prevDays - 1; ++d)
			  for (auto& t : tasks.at(d))
				  tasks.at(days - 1).emplace_back(t);
	  }
	  tasks.resize(days);
    }
    else { //command == "DUMP"
      int d;
      std::cin >> d;
	  std::cout << tasks.at(d - 1).size() << " ";
		for (const auto& t : tasks.at(d - 1))
			std::cout << t << " ";
	    std::cout << std::endl;
    }
  }
  system("pause");
	return 0;
}
