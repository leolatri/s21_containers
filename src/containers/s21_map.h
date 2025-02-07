#ifndef __S21_MAP_H__
#define __S21_MAP_H__

#include "s21_node.h"
#include "s21_vector.h"

namespace s21 {
template <typename Key, typename T>
class map {
 private:
  BinaryNode<Key, T>* root_;
  size_t size_;

 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;
  using node_type = BinaryNode<key_type, mapped_type>;

  class MapIterator : public BinaryIterator<Key, T> {
   public:
    using BinaryIterator<Key, T>::BinaryIterator;

    MapIterator() : BinaryIterator<Key, T>(){};
    MapIterator(node_type* node) : BinaryIterator<Key, T>(node){};
  };

  class MapConstIterator : public MapIterator {
   public:
    MapConstIterator() : MapIterator(){};
    MapConstIterator(node_type* node) : MapIterator(node){};
    MapConstIterator(const MapIterator& obj) : MapIterator(obj.node_){};

    const_reference& operator*() const { return this->node_->value_; }
  };

  using iterator = MapIterator;
  using const_iterator = MapConstIterator;

  map() : size_(0), root_(nullptr) {}

  void clear() {
    root_ = nullptr;
    size_ = 0;
  }

  ~map() { clear(); }

  map(const map& m) {
    this->clear();
    for (iterator i = m.begin(); i != m.end(); ++i) this->insert(*i);
  }

  map(map&& m) : map() {
    this->clear();

    this->size_ = m.size_;
    this->root_ = m.root_;

    m.clear();
  }

  map(std::initializer_list<value_type> const& items) : map() {
    for (const auto& item : items) this->insert(item);
  }

  map operator=(map&& m) {
    this->clear();

    this->size_ = m.size_;
    this->root_ = m.root_;

    m.clear();

    return *this;
  }

  bool operator==(map& other) const {
    if (size_ != other.size_) return false;

    iterator i1 = begin();
    iterator i2 = other.begin();

    while (i1 != end() && i2 != other.end()) {
      if (i1.node_->value_ != i2.node_->value_) return false;
      ++i1;
      ++i2;
    }
    return true;
  }

  map operator=(const map& m) {
    this->clear();
    for (iterator i = m.begin(); i != m.end(); ++i) this->insert(*i);
    return *this;
  }

  bool empty() const { return (size_ == 0); }

  size_type size() { return size_; };
  size_type max_size() {
    return (std::numeric_limits<size_t>::max() / sizeof(T) +
            std::numeric_limits<size_t>::max() / sizeof(Key));
  }

  iterator end() { return iterator(nullptr); }

  const_iterator end() const { return const_iterator(nullptr); }

  iterator last() {
    if (empty()) return end();
    node_type* temp = this->root_;
    while (temp->right_) temp = temp->right_;

    return iterator(temp);
  }

  iterator begin() {
    if (empty()) return end();
    node_type* temp = this->root_;
    while (temp && temp->left_) temp = temp->left_;

    return iterator(temp);
  }

  const_iterator begin() const {
    if (empty()) return end();
    node_type* temp = this->root_;
    while (temp->left_) temp = temp->left_;

    return const_iterator(temp);
  }

  node_type* find(node_type* node, key_type key) {
    if (node == nullptr) return nullptr;
    if (key < node->value_.first)
      return find(node->left_, key);
    else if (key > node->value_.first)
      return find(node->right_, key);
    else
      return node;
  }

  std::pair<iterator, bool> insert(const value_type& value) {
    if (empty()) {
      root_ = new node_type(nullptr, value.first, value.second);
      ++size_;
      return {iterator(root_), true};
    }
    node_type* current = this->root_;

    while (current != nullptr) {
      if (current->value_.first > value.first) {
        if (current->left_)
          current = current->left_;
        else {
          current->left_ = new node_type(current, value.first, value.second);
          ++size_;
          return {iterator(current->left_), true};
        }
      } else if (current->value_.first < value.first) {
        if (current->right_)
          current = current->right_;
        else {
          current->right_ = new node_type(current, value.first, value.second);
          ++size_;
          return {iterator(current->right_), true};
        }
      } else
        return {iterator(current), false};
    }

    return {iterator(current), false};
  }

  void printMap(int num) {
    std::cout << "map " << num << " = { ";
    for (iterator i = begin(); i != end(); ++i) {
      std::cout << "{\"" << i.node_->value_.first << "\" , "
                << i.node_->value_.second << "} ";
      if (i != last()) std::cout << ", ";
    }
    std::cout << " }" << std::endl;
  }

  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    value_type val = value_type(key, obj);
    return this->insert(val);
  }

  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    value_type val = value_type(key, obj);
    node_type* temp = find(root_, key);
    if (temp) {
      temp->value_.second = obj;
      return {iterator(temp), true};
    } else {
      return this->insert(val);
    }
    return {iterator(temp), true};
  }

  T& at(const Key& key) {
    node_type* node = this->find(root_, key);
    return node->value_.second;
  }

  T& operator[](const Key& key) {
    value_type val = value_type(key, T());
    if (find(root_, key) == nullptr) this->insert(val);
    return this->at(key);
  }

  void swap(map& other) {
    map<Key, T> temp = *this;
    *this = other;
    other = temp;
  }

  void erase(iterator pos) {
    if (pos == end()) return;
    map<Key, T> temp;
    for (iterator i = this->begin(); i != this->end(); ++i) {
      if (i != pos) temp.insert(*i);
    }
    *this = temp;
  }

  void merge(map& other) {
    if (empty() && other.empty()) throw std::out_of_range("maps are empty");
    for (iterator i = other.begin(); i != other.end(); ++i) this->insert(*i);
  }

  bool contains(const Key& key) {
    return (this->find(root_, key) ? true : false);
  }

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    s21::vector<std::pair<iterator, bool>> result =
        s21::vector<std::pair<iterator, bool>>();
    const size_type count_of_vargs = sizeof...(args);
    if (!count_of_vargs) return result;

    value_type vargs[count_of_vargs] = {args...};

    for (size_type i = 0; i < count_of_vargs; ++i) {
      result.push_back(this->insert(vargs[i]));
    }
    return result;
  }
};
}  // namespace s21

#endif