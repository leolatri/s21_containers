#ifndef __S21_SET_H__
#define __S21_SET_H__

#include "s21_node.h"

namespace s21 {
template <typename Key>
class set {
 private:
  size_t size_;
  BinaryNodeK<Key>* root_;

 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;
  using node_type = BinaryNodeK<Key>;

  class SetIterator : public BinaryIteratorK<Key> {
   public:
    SetIterator() : BinaryIteratorK<Key>() {}
    SetIterator(node_type* node) : BinaryIteratorK<Key>(node) {}
  };

  class SetConstIterator : public SetIterator {
   public:
    SetConstIterator() : SetIterator() {}
    SetConstIterator(node_type* node) : SetIterator(node) {}
    SetConstIterator(const SetIterator& obj) : SetIterator(obj.node_) {}

    const_reference& operator*() const { return this->node_->value_; }
  };

  using iterator = SetIterator;
  using const_iterator = SetConstIterator;

  set() : size_(0), root_(nullptr){};
  ~set() { clear(); }

  void clear() {
    size_ = 0;
    root_ = nullptr;
  }

  set(const set& s) {
    this->clear();
    for (iterator i = s.begin(); i != s.end(); ++i) this->insert(*i);
  }

  set(set&& s) : set() {
    this->clear();

    this->size_ = s.size_;
    this->root_ = s.root_;

    s.clear();
  }

  set(std::initializer_list<value_type> const& items) : set() {
    for (const auto& item : items) this->insert(item);
  }

  set operator=(set&& s) {
    this->clear();

    this->size_ = s.size_;
    this->root_ = s.root_;

    s.clear();
    return *this;
  }

  set operator=(const set& s) {
    this->clear();
    for (iterator i = s.begin(); i != s.end(); ++i) this->insert(*i);
    return *this;
  }

  bool operator==(const set& other) const {
    if (size_ != other.size_) return false;

    iterator i1 = begin();
    iterator i2 = other.begin();

    while (i1 != end() && i2 != other.end()) {
      if (*i1.node_->value_ != *i2.node_->value_) return false;
      ++i1;
      ++i2;
    }
    return true;
  }

  bool empty() const { return (size_ == 0); }

  size_type size() { return size_; };
  size_type max_size() {
    return (std::numeric_limits<size_t>::max() / sizeof(Key));
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
    if (key < *node->value_)
      return find(node->left_, key);
    else if (key > *node->value_)
      return find(node->right_, key);
    else
      return node;
  }

  std::pair<iterator, bool> insert(const value_type& value) {
    if (empty()) {
      root_ = new node_type(nullptr, value);
      ++size_;
      return {iterator(root_), true};
    }
    node_type* current = this->root_;

    while (current != nullptr) {
      if (*current->value_ > value) {
        if (current->left_)
          current = current->left_;
        else {
          current->left_ = new node_type(current, value);
          ++size_;
          return {iterator(current->left_), true};
        }
      } else if (*current->value_ < value) {
        if (current->right_)
          current = current->right_;
        else {
          current->right_ = new node_type(current, value);
          ++size_;
          return {iterator(current->right_), true};
        }
      } else
        return {iterator(current), false};
    }

    return {iterator(current), false};
  }

  void erase(iterator pos) {
    if (pos == end()) return;
    set<Key> temp;
    for (iterator i = this->begin(); i != this->end(); ++i) {
      if (i != pos) temp.insert(*i);
    }
    *this = temp;
  }

  void swap(set& other) {
    set<Key> temp = *this;
    *this = other;
    other = temp;
  }

  void merge(set& other) {
    if (empty() && other.empty()) throw std::out_of_range("maps are empty");
    for (iterator i = other.begin(); i != other.end(); ++i) this->insert(*i);
  }

  iterator find(const Key& key) { return iterator(this->find(root_, key)); }

  bool contains(const Key& key) {
    return (this->find(root_, key) ? true : false);
  }

  void printSet(int num) {
    std::cout << "set " << num << " = { ";
    for (iterator i = begin(); i != end(); ++i) {
      std::cout << *i.node_->value_;
      if (i != last()) std::cout << ", ";
    }
    std::cout << " }\n" << std::endl;
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