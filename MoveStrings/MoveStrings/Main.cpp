#include <string>
#include <vector>

void MoveStrings(std::vector<std::string>& source, std::vector<std::string>& destination)
{
	for(const auto& s : source) {
		destination.emplace_back(s);
	}
	source.clear();
}

//int main(int argc, char* argv[])
//{
//	std::vector<std::string> source = { "a", "b", "c" };
//	std::vector<std::string> destination = { "z" };
//	MoveStrings(source, destination);
//	system("pause");
//	return 0;
//}
