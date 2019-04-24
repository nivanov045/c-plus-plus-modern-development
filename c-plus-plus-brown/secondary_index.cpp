#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

typedef string ID;

struct Record {
  ID id;
  string title;
  string user;
  int timestamp;
  int karma;
};

class Database {
public:
  bool Put(const Record& record)
  {
    if (_data.count(record.id))
      return false;
    _data.insert({
      record.id,
      make_tuple
      (
        record, _secondaryUserIdx.insert({record.user, record.id}),
        _secondaryTimestampIdx.insert({record.timestamp, record.id}),
        _secondaryKarmaIdx.insert({record.karma, record.id})
      )
    });
    return true;
  }

  const Record* GetById(const ID& id) const
  {
    if (_data.count(id))
      return &get<0>(_data.at(id));
    return nullptr;
  }

  bool Erase(const ID& id)
  {
    if (!_data.count(id))
      return false;
    auto dataElement = _data.at(id);
    _secondaryUserIdx.erase(get<1>(dataElement));
    _secondaryTimestampIdx.erase(get<2>(dataElement));
    _secondaryKarmaIdx.erase(get<3>(dataElement));
    _data.erase(id);
    return true;
  }

  template <typename Callback>
  void RangeByTimestamp(int low, int high, Callback callback) const
  {
    for (auto it = _secondaryTimestampIdx.lower_bound(low); it != _secondaryTimestampIdx.upper_bound(high); ++it) {
      const auto& rec = get<0>(_data.at(it->second));
      if (!callback(rec))
        return;
    }
  }

  template <typename Callback>
  void RangeByKarma(int low, int high, Callback callback) const
  {
    for (auto it = _secondaryKarmaIdx.lower_bound(low); it != _secondaryKarmaIdx.upper_bound(high); ++it) {
      const auto& rec = get<0>(_data.at(it->second));
      if (!callback(rec))
        return;
    }
  }

  template <typename Callback>
  void AllByUser(const string& user, Callback callback) const
  {
    for (auto it = _secondaryUserIdx.lower_bound(user); it != _secondaryUserIdx.upper_bound(user); ++it) {
      const auto& rec = get<0>(_data.at(it->second));
      if (!callback(rec))
        return;
    }
  }
private:
  map<ID, tuple<Record, multimap<string, ID>::iterator, multimap<int, ID>::iterator, multimap<int, ID>::iterator>> _data;
  multimap<int, ID> _secondaryKarmaIdx;
  multimap<int, ID> _secondaryTimestampIdx;
  multimap<string, ID> _secondaryUserIdx;
};

void TestRangeBoundaries() {
  const int good_karma = 1000;
  const int bad_karma = -10;

  Database db;
  db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
  db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

  int count = 0;
  db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestSameUser() {
  Database db;
  db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
  db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

  int count = 0;
  db.AllByUser("master", [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestReplacement() {
  const string final_body = "Feeling sad";

  Database db;
  db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
  db.Erase("id");
  db.Put({"id", final_body, "not-master", 1536107260, -10});

  auto record = db.GetById("id");
  ASSERT(record != nullptr);
  ASSERT_EQUAL(final_body, record->title);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestRangeBoundaries);
  RUN_TEST(tr, TestSameUser);
  RUN_TEST(tr, TestReplacement);
  return 0;
}
