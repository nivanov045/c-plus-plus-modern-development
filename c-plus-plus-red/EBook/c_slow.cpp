#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <string>

using namespace std;

class ReadingManager {
public:
  ReadingManager()
    : user_page_counts_(MAX_USER_COUNT_ + 1, 0),
      num_of_read_page_(MAX_PAGE_COUNT_ + 1, 0), 
      numOfUsers(0)
  {
  }

  void Read(int user_id, int page_count) {
    if (user_page_counts_[user_id] == 0) {
      AddUser();
    }
    const auto prev_page_count = user_page_counts_[user_id];
    user_page_counts_[user_id] = page_count;
    for (auto it = prev_page_count + 1; it <= page_count; ++it)
      ++num_of_read_page_[it];
  }

  double Cheer(int user_id) const {
    if (user_page_counts_[user_id] == 0) {
      return 0;
    }
    const int user_count = GetUserCount();
    if (user_count == 1) {
      return 1;
    }
    const int page_count = user_page_counts_[user_id];
    return (num_of_read_page_[1] - num_of_read_page_[page_count]) * 1.0 / (user_count - 1);
  }

private:
  static const int MAX_USER_COUNT_ = 100'000;
  static const int MAX_PAGE_COUNT_ = 1000;

  vector<int> user_page_counts_;
  vector<int> num_of_read_page_;  //# прочитавших страницу
  int numOfUsers;

  int GetUserCount() const {
    return numOfUsers;
  }
  void AddUser() {
    ++numOfUsers;
  }
};


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}