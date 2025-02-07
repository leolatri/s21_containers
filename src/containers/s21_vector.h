#ifndef __S21_VECTOR_H__
#define __S21_VECTOR_H__

#include "s21_node.h"

namespace s21 {
template <typename T>
class vector {
 private:
  size_t size_of_vector;
  size_t capacity_of_vector;
  T* array_;

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;
  using iterator = T*;
  using const_iterator = const T*;

  vector()
      : size_of_vector(0),
        capacity_of_vector(1),
        array_(new T[capacity_of_vector]) {}
  ~vector() {
    size_of_vector = 0;
    capacity_of_vector = 0;
    delete[] array_;
  }

  vector(size_type n)
      : size_of_vector(n), capacity_of_vector(n), array_(new T[n]) {}

  vector(std::initializer_list<value_type> const& items) : vector() {
    for (const auto& item : items) {
      push_back(item);
    }
  }

  vector(const vector& v) : vector(v.size_of_vector) {
    for (size_t i = 0; i < size_of_vector; ++i) {
      array_[i] = v.array_[i];
    }
  }

  vector(vector&& v) {
    size_of_vector = v.size_of_vector;
    capacity_of_vector = v.capacity_of_vector;
    array_ = v.array_;

    v.capacity_of_vector = 0;
    v.size_of_vector = 0;
    v.array_ = nullptr;
  }

  vector& operator=(const vector& v) {
    delete[] array_;
    size_of_vector = v.size_of_vector;
    capacity_of_vector = v.capacity_of_vector;
    array_ = new T[capacity_of_vector];
    for (size_t i = 0; i < size_of_vector; ++i) {
      array_[i] = v.array_[i];
    }
    return *this;
  }

  vector& operator=(vector&& v) {
    size_of_vector = v.size_of_vector;
    capacity_of_vector = v.capacity_of_vector;
    array_ = v.array_;

    v.capacity_of_vector = 0;
    v.size_of_vector = 0;
    v.array_ = nullptr;

    return *this;
  }
  reference operator[](size_type pos) {
    if (pos < 0 || pos >= size_of_vector)
      throw std::out_of_range("Item doesn't exist");
    return array_[pos];
  }

  bool operator==(vector& v) {
    if (size() != v.size()) return false;
    for (size_t i = 0; i < size(); ++i) {
      if (v.array_[i] != array_[i]) return false;
    }
    return true;
  };

  void push_back(const_reference value) {
    this->reserve(this->size_of_vector + 1);
    this->size_of_vector++;

    this->array_[size_of_vector - 1] = value;
  }

  void printVector(int num) {
    std::cout << "vector " << num << " = {";
    for (size_t i = 0; i < size_of_vector; ++i) {
      if (i != 0) std::cout << ", ";
      std::cout << array_[i];
    }
    std::cout << "}" << std::endl;
  }

  reference at(size_type pos) {
    if (pos < 0 || pos >= size_of_vector)
      throw std::out_of_range("Item doesn't exist");
    for (size_t i = 0; i < size_of_vector; ++i) {
      if (i == pos) return array_[i];
    }
  }

  const_reference front() { return array_[0]; }

  const_reference back() { return array_[size_of_vector - 1]; }

  T* data() { return array_; }

  iterator begin() { return array_; }

  const_iterator cbegin() const { return array_; }

  iterator end() {
    if (this->empty()) return this->array_;
    return this->array_ + this->size_of_vector;
  }

  bool empty() { return (size_of_vector == 0); }

  size_type size() { return size_of_vector; }

  size_type capacity() { return capacity_of_vector; }

  size_type max_size() {
    return std::numeric_limits<size_t>::max() / sizeof(T);
  }

  void reserve(size_type size) {
    if (size <= this->capacity_of_vector) return;

    value_type* new_array = new value_type[size + 1]();
    for (size_type i = 0; i < this->size_of_vector; ++i) {
      new_array[i] = this->array_[i];
    }

    delete[] this->array_;
    this->array_ = new_array;
    this->capacity_of_vector = size;
  }

  void shrink_to_fit() {
    if (this->size_of_vector == this->capacity_of_vector) return;

    value_type* new_array = new value_type[this->size_of_vector + 1]();
    for (size_type i = 0; i < this->size_of_vector; ++i)
      new_array[i] = this->array_[i];

    delete[] this->array_;

    this->array_ = new_array;
    this->capacity_of_vector = this->size_of_vector;
  }

  void clear() {
    delete[] array_;
    size_of_vector = 0;
    capacity_of_vector = 0;
    array_ = new T[1]();
  }

  iterator insert(iterator pos, const_reference value) {  //?
    size_type pos_index = pos - this->array_;

    this->reserve(this->size_of_vector + 1);
    pos = this->array_ + pos_index;

    for (iterator i = this->end(); i != pos; --i) *i = *(i - 1);
    *pos = value;

    ++this->size_of_vector;
    return pos;
  }

  void erase(iterator pos) {
    size_t index = pos - array_;
    pos = array_ + index;

    vector<T> temp;
    for (size_t i = 0; i < size_of_vector; ++i) {
      if (i != index) temp.push_back(array_[i]);
    }
    *this = temp;
  }

  void pop_back() {
    if (this->empty()) throw std::out_of_range("vector is empty");
    this->array_[--this->size_of_vector] = 0;
  }

  void swap(vector& other) {
    vector<T> temp = other;
    other = *this;
    *this = temp;

    temp.clear();
  }

  template <typename... Args>  //?
  iterator insert_many(const_iterator pos, Args&&... args) {
    const size_type count_of_vargs = sizeof...(args);
    if (!count_of_vargs) return (iterator)pos;

    iterator iter = (iterator)pos;

    value_type vargs[count_of_vargs] = {args...};
    for (size_type i = 0; i < count_of_vargs; ++i) {
      iter = this->insert(iter, vargs[i]) + 1;
    }

    return iter;
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    for (const auto& arg : {args...}) push_back(arg);
  }
};

}  // namespace s21

#endif