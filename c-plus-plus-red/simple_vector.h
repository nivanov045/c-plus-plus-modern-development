#pragma once

#include <algorithm>
#include <iterator>
using namespace std;

template <typename T>
class SimpleVector {
public:
  SimpleVector() = default;
  explicit SimpleVector(size_t size);
  ~SimpleVector();

  SimpleVector<T>& operator=(const SimpleVector& rhs);

  T& operator[](size_t index);

  T* begin();
  T* end();
  const T* begin() const;
  const T* end() const;

  size_t Size() const;
  size_t Capacity() const;
  void PushBack(const T& value);

private:
  T* data = nullptr;
  size_t size = 0;
  size_t capacity = 0;
};

template <typename T>
SimpleVector<T>::SimpleVector(size_t size)
  : data(new T[size])
  , size(size)
  , capacity(size)
{
}

template <typename T>
SimpleVector<T>::~SimpleVector() {
  delete[] data;
}

template <typename T>
SimpleVector<T>& SimpleVector<T>::operator=(const SimpleVector<T>& other) {
  delete[] this->data;
  this->data = new T[other.capacity];
  this->capacity = other.capacity;
  this->size = other.size;
  copy(make_move_iterator(other.begin()), make_move_iterator( other.end()), this->begin());
  return *this;
}

template <typename T>
T& SimpleVector<T>::operator[](size_t index) {
  return data[index];
}

template <typename T>
size_t SimpleVector<T>::Size() const {
  return size;
}

template <typename T>
size_t SimpleVector<T>::Capacity() const {
  return capacity;
}

template <typename T>
void SimpleVector<T>::PushBack(const T& value) {
  if (size >= capacity) {
    auto new_cap = capacity == 0 ? 1 : 2 * capacity;
    auto new_data = new T[new_cap];
    copy(begin(), end(), new_data);
    delete[] data;
    data = new_data;
    capacity = new_cap;
  }
  data[size++] = value;
}

template <typename T>
T* SimpleVector<T>::begin() {
  return data;
}

template <typename T>
T* SimpleVector<T>::end() {
  return data + size;
}

template <typename T>
const T* SimpleVector<T>::begin() const
{
  return data;
}

template <typename T>
const T* SimpleVector<T>::end() const
{
  return data + size;
}
