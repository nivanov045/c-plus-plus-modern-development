#include <iostream>
#include <string>
#include <mutex>

class ReversibleString
{
public:
	ReversibleString(const std::string& iString) : _string(iString)
	{
	}
	ReversibleString() : _string("")
	{
	}
	void Reverse()
	{
		const int length = _string.length();
		for(int i = 0; i < length / 2; i++) {
			std::swap(_string[i], _string[length - 1 - i]);
		}
	}
	std::string ToString() const
	{
		return _string;
	}
private:
	std::string _string;
};

//int main() {
//	ReversibleString s("live");
//	s.Reverse();
//	std::cout << s.ToString() << std::endl;
//
//	s.Reverse();
//	const ReversibleString& s_ref = s;
//	std::string tmp = s_ref.ToString();
//	std::cout << tmp << std::endl;
//
//	ReversibleString empty;
//	std::cout << '"' << empty.ToString() << '"' << std::endl;
//
//	return 0;
//}
