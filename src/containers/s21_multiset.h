#ifndef __S21_MULTISET_H__
#define __S21_MULTISET_H__

#include "s21_node.h"

namespace s21 {
template <typename Key>
class multiset {
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

  class MultisetIterator : public BinaryIteratorK<Key> {
   public:
    MultisetIterator() : BinaryIteratorK<Key>() {}
    MultisetIterator(node_type* node) : BinaryIteratorK<Key>(node) {}
  };

  class MultisetConstIterator : public MultisetIterator {
   public:
    MultisetConstIterator() : MultisetIterator() {}
    MultisetConstIterator(node_type* node) : MultisetIterator(node) {}
    MultisetConstIterator(const MultisetIterator& obj)
        : MultisetIterator(obj.node_) {}

    const_reference& operator*() const { return this->node_->value_; }
  };

  using iterator = MultisetIterator;
  using const_iterator = MultisetConstIterator;

  multiset() : size_(0), root_(nullptr){};
  ~multiset() { clear(); }

  void clear() {
    size_ = 0;
    root_ = nullptr;
  }

  multiset(const multiset& s) {
    this->clear();
    for (iterator i = s.begin(); i != s.end(); ++i) this->insert(*i);
  }

  multiset(multiset&& s) : multiset() {
    this->clear();

    this->size_ = s.size_;
    this->root_ = s.root_;

    s.clear();
  }

  multiset(std::initializer_list<value_type> const& items) : multiset() {
    for (const auto& item : items) this->insert(item);
  }

  multiset operator=(multiset&& s) {
    this->clear();

    this->size_ = s.size_;
    this->root_ = s.root_;

    s.clear();
    return *this;
  }

  bool operator==(const multiset& other) const {
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

  multiset operator=(const multiset& s) {
    this->clear();
    for (iterator i = s.begin(); i != s.end(); ++i) this->insert(*i);
    return *this;
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
      if (*current->value_ >= value) {
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
      }
    }

    return {iterator(current), false};
  }

  void erase(iterator pos) {
    if (pos == end()) return;
    multiset<Key> temp;
    for (iterator i = this->begin(); i != this->end(); ++i) {
      if (i != pos) temp.insert(*i);
    }
    *this = temp;
  }

  void swap(multiset& other) {
    multiset<Key> temp = *this;
    *this = other;
    other = temp;
  }

  void merge(multiset& other) {
    if (empty() && other.empty()) throw std::out_of_range("maps are empty");
    for (iterator i = other.begin(); i != other.end(); ++i) this->insert(*i);
  }

  iterator find(const Key& key) { return iterator(this->find(root_, key)); }

  bool contains(const Key& key) {
    return (this->find(root_, key) ? true : false);
  }

  void printMultiset(int num) {
    std::cout << "multiset " << num << " = { ";
    for (iterator i = begin(); i != end(); ++i) {
      std::cout << *i.node_->value_;
      if (i != last()) std::cout << ", ";
    }
    std::cout << " }\n" << std::endl;
  }

  std::pair<iterator, iterator> equal_range(const Key& key) {
    std::pair<iterator, iterator> result =
        std::pair<iterator, iterator>(this->end(), this->end());
    iterator start = begin();
    iterator end = last();

    for (; start != find(key); ++start)
      ;
    for (; end != ++find(key); --end)
      ;

    result.first = start;
    result.second = end;

    return result;
  }

  iterator lower_bound(const Key& key) {
    if (find(root_, key) != nullptr) return find(key);
    for (iterator i = begin(); i != end(); ++i) {
      if (*i >= key) return i;
    }
    return begin();
  }

  iterator upper_bound(const Key& key) {
    for (iterator i = begin(); i != end(); ++i) {
      if (*i > key) return i;
    }
    return begin();
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