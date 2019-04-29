#include <iostream>
#include <exception>
#include <string>
using namespace std;

string AskTimeServer() {
	//throw system_error(error_code());
	throw exception(invalid_argument("qwe"));
	return "11:11:11";
}

class TimeServer {
public:
    string GetCurrentTime() {
	    try {
			LastFetchedTime = AskTimeServer();
			return LastFetchedTime;
	    }
	    catch (system_error& ex) {
			return LastFetchedTime;
	    }
    }

private:
    string LastFetchedTime = "00:00:00";
};

int main() {
    TimeServer ts;
    try {
        cout << ts.GetCurrentTime() << endl;
    } catch (exception& e) {
        cout << "Exception got: " << e.what() << endl;
    }
    return 0;
}
