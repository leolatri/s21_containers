#ifndef __S21_ARRAY_H__
#define __S21_ARRAY_H__

#include "s21_node.h"

namespace s21 {
template <typename T, size_t N>
class array {
 private:
  T* array_;

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;
  using iterator = T*;
  using const_iterator = const T*;

  array() : array_(new T[N]()){};
  ~array() { delete[] array_; }

  reference operator[](size_t index) {
    if (index >= N) throw std::out_of_range("Not correct index");
    return array_[index];
  };

  const_reference operator[](size_t index) const {
    if (index >= N) throw std::out_of_range("Not correct index");
    return array_[index];
  };

  size_type size() { return N; };

  array(const array& a) : array() {
    for (size_t i = 0; i < N; ++i) {
      array_[i] = a.array_[i];
    }
  };

  array(array&& a) {
    array_ = a.array_;
    a.~array();
  }

  array& operator=(array& a) {
    if (size() != a.size()) throw std::out_of_range("Different sizes!!!");  //?
    for (size_t i = 0; i < size(); ++i) {
      array_[i] = a.array_[i];
    }
    return *this;
  };

  bool operator==(array& a) {
    if (size() != a.size()) return false;
    for (size_t i = 0; i < size(); ++i) {
      if (a.array_[i] != array_[i]) return false;
    }
    return true;
  };

  array& operator=(array&& a) {
    if (this != a) {
      this->~array();
      this->array_ = a.array_;
      a.array_ = nullptr;
    }
    return *this;
  };

  array(std::initializer_list<value_type> const& items) : array_(new T[N]()) {
    if (N < 1)
      throw std::out_of_range("Array size must be greater than 0");  //?
    if (items.size() > N) throw std::out_of_range("big size of items!!!");
    size_t i = 0;
    for (const auto& item : items) {
      if (i < N) array_[i++] = item;
    }
  };

  void printArray(int num) {
    std::cout << "array " << num << "= {";
    for (size_t i = 0; i < size() - 1; ++i) {
      std::cout << array_[i] << ", ";
    }
    std::cout << array_[size() - 1] << "";
    std::cout << "}" << std::endl;
  };

  reference at(size_type pos) {
    if (pos < 0 || pos >= N) throw std::out_of_range("Item doesn't exist");
    for (size_t i = 0; i < N; ++i) {
      if (i == pos) return array_[i];
    }
  };

  const_reference front() { return array_[0]; };

  const_reference back() { return array_[N - 1]; };

  iterator data() { return array_; };

  const_iterator data() const { return array_; };

  iterator begin() { return iterator(data()); };

  iterator end() { return iterator(nullptr); };

  bool empty() { return (N == 0); };

  size_type max_size() {  //?
    return std::numeric_limits<size_t>::max() / sizeof(T);
  };

  void swap(array& other) {
    for (size_t i = 0; i < N; ++i) {
      T temp = array_[i];
      array_[i] = other.array_[i];
      other.array_[i] = temp;
    }
  };

  void fill(const_reference value) {
    for (size_t i = 0; i < N; ++i) {
      array_[i] = value;
    }
  }
};
}  // namespace s21

#endif
