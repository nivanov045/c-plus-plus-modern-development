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

struct DataElement
{
  Record record;
  multimap<string, const Record*>::iterator userIdx;
  multimap<int, const Record*>::iterator timestampIdx;
  multimap<int, const Record*>::iterator karmaIdx;
};

class Database
{
public:
  bool Put(const Record& record)
  {
    const auto resOfInsert = _data.insert({ record.id, {record, {}, {}, {}} });
    if (!resOfInsert.second)
      return false;
    auto it = resOfInsert.first;
    auto& data = it->second;
    auto recPointer = &data.record;

    data.userIdx = _secondaryUserIdx.insert({ record.user, recPointer });
    data.timestampIdx = _secondaryTimestampIdx.insert({ record.timestamp, recPointer });
    data.karmaIdx = _secondaryKarmaIdx.insert({ record.karma, recPointer });
    return true;
  }

  const Record* GetById(const ID& id) const
  {
    auto it = _data.find(id);
    if (it != _data.end())
      return &it->second.record;
    return nullptr;
  }

  bool Erase(const ID& id)
  {
    auto it = _data.find(id);
    if (it == _data.end())
      return false;
    const auto& secondaryIdxs = it->second;
    _secondaryUserIdx.erase(secondaryIdxs.userIdx);
    _secondaryTimestampIdx.erase(secondaryIdxs.timestampIdx);
    _secondaryKarmaIdx.erase(secondaryIdxs.karmaIdx);
    _data.erase(it);
    return true;
  }

  template <typename Callback>
  void RangeByTimestamp(int low, int high, Callback callback) const
  {
    auto lb = _secondaryTimestampIdx.lower_bound(low);
    auto ub = _secondaryTimestampIdx.upper_bound(high);
    for (auto it = lb; it != ub; ++it) {
      if (!callback(*it->second))
        return;
    }
  }

  template <typename Callback>
  void RangeByKarma(int low, int high, Callback callback) const
  {
    auto lb = _secondaryKarmaIdx.lower_bound(low);
    auto ub = _secondaryKarmaIdx.upper_bound(high);
    for (auto it = lb; it != ub; ++it) {
      if (!callback(*it->second))
        return;
    }
  }

  template <typename Callback>
  void AllByUser(const string& user, Callback callback) const
  {
    auto er = _secondaryUserIdx.equal_range(user);
    for (auto it = er.first; it != er.second; ++it) {
      if (!callback(*it->second))
        return;
    }
  }

private:
  unordered_map<ID, DataElement> _data;
  multimap<int, const Record*> _secondaryKarmaIdx;
  multimap<int, const Record*> _secondaryTimestampIdx;
  multimap<string, const Record*> _secondaryUserIdx;
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
