#pragma once

#include <cstdlib>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
  SimpleVector(): _begin(new T[0]), _end(_begin), _capacity(0) {}

  explicit SimpleVector(size_t size) : _begin(new T[size]), _end(_begin + size), _capacity(size) {}

  ~SimpleVector() { delete[] _begin; }

  T& operator[](size_t index) { return _begin[index]; }

  T* begin() { return _begin; }
  T* end() { return _end; }  
  
  const T* begin() const { return _begin; }
  T* end() const { return _end; }

  size_t Size() const { return _end - _begin; }
  size_t Capacity() const { return _capacity; }
  
  void PushBack(const T& value)
  {
    if (Capacity() == 0)
      resize(1u);
    if (Size() == Capacity()) {
      resize(Capacity() * 2);
    }
    *_end = value;
    ++_end;
  }

private:
  void resize(size_t newCapacity)
  {
    if (newCapacity < Capacity())
      return;
    T* newBegin = new T[newCapacity];
    for (size_t i = 0; i != Size(); ++i) {
      newBegin[i] = _begin[i];
    }
    const auto size = Size();
    delete[] _begin;
    _begin = newBegin;
    _end = _begin + size;
    _capacity = newCapacity;
  }
  // Добавьте поля для хранения данных вектора
  T* _begin;
  T* _end;
  size_t _capacity;
};
