#include <string>
#include <map>
#include <iostream>
#include <iomanip>
#include <vector>
#include <deque>

using namespace std;

struct Query
{
  long long time;
  string hotelName;
  int clientID;
  int roomCount;
};

class BookingSystem
{
public:
  BookingSystem() = default;
  void Book(long long iTime, const string& iHotelName, int iClientID, int iRoomCount)
  {
    _currentTime = iTime;
    queries.push_front({ iTime, iHotelName, iClientID, iRoomCount });
    _numOfRoomsForLastDay[iHotelName] += iRoomCount;
    _numOfClientsForLastDay[iHotelName][iClientID] += 1;
    long long lastTime = queries.back().time;
    while (lastTime <= iTime - 86400) {
      auto qForDel = queries.back();
      _numOfRoomsForLastDay[qForDel.hotelName] -= qForDel.roomCount;
       if (_numOfClientsForLastDay[qForDel.hotelName][qForDel.clientID] == 1) {
         _numOfClientsForLastDay[qForDel.hotelName].erase(qForDel.clientID);
       }
       else {
         _numOfClientsForLastDay[qForDel.hotelName][qForDel.clientID] -= 1;
       }

      queries.pop_back();
      lastTime = queries.back().time;
    }
  }
  int GetNumOfClients(const string& iHotelName) const
  {
    if (_numOfClientsForLastDay.count(iHotelName))
      return _numOfClientsForLastDay.at(iHotelName).size();
    return 0;
  }
  int GetNumOfRooms(const string& iHotelName) const
  {
    if (_numOfRoomsForLastDay.count(iHotelName))
      return _numOfRoomsForLastDay.at(iHotelName);
    return 0;
  }
private:
  long long _currentTime{};
  map <string, map<int, int>> _numOfClientsForLastDay;
  map<string, int> _numOfRoomsForLastDay;
  deque<Query> queries;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  BookingSystem bs;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    string hotelName;
    if (query_type == "BOOK") {
      long long time;  int clientID; int roomCount;
      cin >> time >> hotelName >> clientID >> roomCount;
      bs.Book(time, hotelName, clientID, roomCount);
    }
    else if (query_type == "CLIENTS") {
      cin >> hotelName;
      cout << bs.GetNumOfClients(hotelName) << "\n";
    }
    else if (query_type == "ROOMS") {
      cin >> hotelName;
      cout << bs.GetNumOfRooms(hotelName) << "\n";
    }
  }
  system("pause");
  return 0;
}