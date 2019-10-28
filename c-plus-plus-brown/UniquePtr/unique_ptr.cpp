#include "test_runner.h"

#include <cstddef>  // нужно для nullptr_t

using namespace std;

// Реализуйте шаблон класса UniquePtr
template <typename T>
class UniquePtr {
private:
  T* _object;
public:
  UniquePtr()
  {
    _object = nullptr;
  }
  UniquePtr(T * ptr)
  {
    _object = ptr;
  }
  UniquePtr(const UniquePtr&) = delete;
  UniquePtr(UniquePtr&& other) {
    _object = std::move(other._object);
    other._object = nullptr;
  }
  UniquePtr& operator= (const UniquePtr&) = delete;
  UniquePtr& operator= (nullptr_t)
  {
    delete _object;
    _object = nullptr;
    return *this;
  }
  UniquePtr& operator= (UniquePtr&& other)
  {
    _object = std::move(other._object);
    other._object = nullptr;
    return *this;
  }
  ~UniquePtr()
  {
    delete _object;
  }
    
  T& operator * () const
  {
    return *_object;
  }

  T* operator -> () const
  {
    return _object;
  }

  T* Release()
  {
    auto result = std::move(_object);
    _object = nullptr;
    return result;
  }

  void Reset(T * ptr)
  {
    delete _object;
    _object = ptr;
  }

  void Swap(UniquePtr& other)
  {
    std::swap(other._object, _object);
  }

  T * Get() const
  {
    return _object;
  }
};


struct Item {
  static int counter;
  int value;
  Item(int v = 0): value(v) {
    ++counter;
  }
  Item(const Item& other): value(other.value) {
    ++counter;
  }
  ~Item() {
    --counter;
  }
};

int Item::counter = 0;


void TestLifetime() {
  Item::counter = 0;
  {
    UniquePtr<Item> ptr(new Item);
    ASSERT_EQUAL(Item::counter, 1);

    ptr.Reset(new Item);
    ASSERT_EQUAL(Item::counter, 1);
  }
  ASSERT_EQUAL(Item::counter, 0);

  {
    UniquePtr<Item> ptr(new Item);
    ASSERT_EQUAL(Item::counter, 1);

    auto rawPtr = ptr.Release();
    ASSERT_EQUAL(Item::counter, 1);

    delete rawPtr;
    ASSERT_EQUAL(Item::counter, 0);
  }
  ASSERT_EQUAL(Item::counter, 0);
}

void TestGetters() {
  UniquePtr<Item> ptr(new Item(42));
  ASSERT_EQUAL(ptr.Get()->value, 42);
  ASSERT_EQUAL((*ptr).value, 42);
  ASSERT_EQUAL(ptr->value, 42);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestLifetime);
  RUN_TEST(tr, TestGetters);
}
