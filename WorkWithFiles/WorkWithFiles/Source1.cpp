#include <fstream>
#include <string>
#include <iostream>

int main(int argc, char* argv[])
{
	std::ifstream stream("input.txt");
	std::ofstream outStream("output.txt");
	std::string line;
	while (std::getline(stream, line)) {
		outStream << line << std::endl;
	}
	return 0;
}
