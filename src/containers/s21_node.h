#ifndef __S21_NODE_H__
#define __S21_NODE_H__

#include <initializer_list>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <utility>

template <typename T>
struct NodeTwo {
  T value;
  NodeTwo* next;
  NodeTwo* prev;

  NodeTwo(T val) : value(val), next(nullptr), prev(nullptr) {}
};

template <typename T>
struct Node {
  T value;
  Node* next;

  Node(T val) : value(val), next(nullptr) {}
};

template <typename T>
class IteratorTwo {
 public:
  NodeTwo<T>* node_;
  IteratorTwo(NodeTwo<T>* node) : node_(node) {}

  bool operator!=(const IteratorTwo<T>& other) const {
    return (node_ != other.node_);
  }

  bool operator==(const IteratorTwo<T>& other) const {
    return (node_ == other.node_);
  }

  T& operator*() { return node_->value; }

  IteratorTwo<T>& operator++() {
    if (node_) {
      node_ = node_->next;
    }
    return *this;
  }

  IteratorTwo<T> operator++(int) {
    IteratorTwo<T> temp = *this;
    if (node_) {
      node_ = node_->next;
    }
    return temp;
  }

  IteratorTwo<T>& operator--() {
    if (node_) {
      node_ = node_->prev;
    }
    return *this;
  }

  IteratorTwo<T> operator--(int) {
    IteratorTwo<T> temp = *this;
    if (node_) {
      node_ = node_->prev;
    }
    return temp;
  }
};

template <typename T>
class Iterator {
 public:
  Node<T>* node_;
  Iterator(NodeTwo<T>* node) : node_(node) {}

  bool operator!=(const Iterator<T>& other) const {
    return (node_ != other.node_);
  }

  bool operator==(const Iterator<T>& other) const {
    return (node_ == other.node_);
  }

  T& operator*() { return node_->value; }

  Iterator<T>& operator++() {
    if (node_) {
      node_ = node_->next;
    }
    return *this;
  }

  Iterator<T> operator++(int) {
    Iterator<T> temp = *this;
    if (node_) {
      node_ = node_->next;
    }
    return temp;
  }

  Iterator<T>& operator--() {
    if (node_) {
      node_ = node_->prev;
    }
    return *this;
  }

  Iterator<T> operator--(int) {
    Iterator<T> temp = *this;
    if (node_) {
      node_ = node_->prev;
    }
    return temp;
  }
};

template <typename Key, typename T>
class BinaryNode {
 public:
  using value_type = std::pair<const Key, T>;
  value_type value_;
  BinaryNode<Key, T>* left_;
  BinaryNode<Key, T>* right_;
  BinaryNode<Key, T>* parent_;

  BinaryNode()
      : parent_(nullptr), left_(nullptr), right_(nullptr), value_(Key(), T()) {}
  BinaryNode(BinaryNode<Key, T>* parent, const Key& key, const T& obj)
      : parent_(parent), value_(key, obj), left_(nullptr), right_(nullptr){};
};

template <typename Key, typename T>
class BinaryIterator {
 public:
  BinaryNode<Key, T>* node_;

  BinaryIterator() : node_(nullptr) {}
  BinaryIterator(BinaryNode<Key, T>* node) : node_(node) {}

  bool operator!=(const BinaryIterator<Key, T>& other) const {
    return (node_ != other.node_);
  }

  bool operator==(const BinaryIterator<Key, T>& other) const {
    return (node_ == other.node_);
  }

  std::pair<const Key, T>& operator*() { return node_->value_; }

  BinaryIterator& operator++() {
    if (node_) {
      if (node_->right_) {
        node_ = node_->right_;
        while (node_->left_) {
          node_ = node_->left_;
        }
      } else {
        BinaryNode<Key, T>* parent = node_->parent_;
        while (parent && node_ == parent->right_) {
          node_ = parent;
          parent = parent->parent_;
        }
        node_ = parent;
      }
    }
    return *this;
  }

  BinaryIterator& operator--() {
    if (node_) {
      if (node_->left_) {
        node_ = node_->left_;
        while (node_->right_) {
          node_ = node_->right_;
        }
      } else {
        BinaryNode<Key, T>* parent = node_->parent_;
        while (parent && node_ == parent->left_) {
          node_ = parent;
          parent = parent->parent_;
        }
        node_ = parent;
      }
    }
    return *this;
  }
};

template <typename Key>
class BinaryNodeK {
 public:
  BinaryNodeK<Key>* parent_;
  BinaryNodeK<Key>* left_;
  BinaryNodeK<Key>* right_;
  Key* value_;

  BinaryNodeK()
      : parent_(nullptr), left_(nullptr), right_(nullptr), value_(nullptr) {}
  BinaryNodeK(BinaryNodeK<Key>* parent, const Key& obj)
      : parent_(parent),
        value_(new Key(obj)),
        left_(nullptr),
        right_(nullptr){};
  ~BinaryNodeK() { delete value_; }
};

template <typename Key>
class BinaryIteratorK {
 public:
  BinaryNodeK<Key>* node_;

  BinaryIteratorK() : node_(nullptr){};
  BinaryIteratorK(BinaryNodeK<Key>* node) : node_(node){};

  bool operator!=(const BinaryIteratorK<Key>& other) const {
    return (node_ != other.node_);
  }

  bool operator==(const BinaryIteratorK<Key>& other) const {
    return (node_ == other.node_);
  }

  Key& operator*() { return *node_->value_; }

  BinaryIteratorK& operator++() {
    if (node_) {
      if (node_->right_) {
        node_ = node_->right_;
        while (node_->left_) {
          node_ = node_->left_;
        }
      } else {
        BinaryNodeK<Key>* parent = node_->parent_;
        while (parent && node_ == parent->right_) {
          node_ = parent;
          parent = parent->parent_;
        }
        node_ = parent;
      }
    }
    return *this;
  }

  BinaryIteratorK& operator--() {
    if (node_) {
      if (node_->left_) {
        node_ = node_->left_;
        while (node_->right_) {
          node_ = node_->right_;
        }
      } else {
        BinaryNodeK<Key>* parent = node_->parent_;
        while (parent && node_ == parent->left_) {
          node_ = parent;
          parent = parent->parent_;
        }
        node_ = parent;
      }
    }
    return *this;
  }
};

#endif