#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate()
  {
    if (_deallocatedObjects.empty()) {
      auto* objPtr = new T;
      _allocatedObjects.insert(objPtr);
      return objPtr;
    }
    auto* objPtr = _deallocatedObjects.front();
    _deallocatedObjects.pop();
    _allocatedObjects.insert(objPtr);
    return objPtr;
  }

  T* TryAllocate()
  {
    if (_deallocatedObjects.empty())
      return nullptr;
    auto* objPtr = _deallocatedObjects.front();
    _deallocatedObjects.pop();
    _allocatedObjects.insert(objPtr);
    return objPtr;
  }

  void Deallocate(T* object)
  {
    if (_allocatedObjects.count(object)) {
      _deallocatedObjects.push(object);
      _allocatedObjects.erase(object);
    }
    else {
      throw invalid_argument("No such allocated object!");
    }
  }

  ~ObjectPool()
  {
    while(!_deallocatedObjects.empty()) {
      auto objPtr = _deallocatedObjects.front();
      _deallocatedObjects.pop();
      delete objPtr;
    }
    for (auto* o : _allocatedObjects)
      delete o;
  }

private:
  queue<T*> _deallocatedObjects;
  set<T*> _allocatedObjects;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
