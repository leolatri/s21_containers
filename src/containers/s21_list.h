#ifndef __S21_LIST_H__
#define __S21_LIST_H__

#include "s21_node.h"

namespace s21 {
template <typename T>
class list {
 private:
  size_t size_of_list;
  size_t current_size;
  NodeTwo<T>* top_of_list;
  NodeTwo<T>* tail_of_list;

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  class ListIterator : public IteratorTwo<T> {
   public:
    ListIterator() : IteratorTwo<T>(nullptr) {}
    ListIterator(NodeTwo<T>* node) : IteratorTwo<T>(node) {}

    ListIterator& operator++() {
      if (this->node_) this->node_ = this->node_->next;
      return *this;
    }

    ListIterator& operator--() {
      if (this->node_) this->node_ = this->node_->prev;
      return *this;
    }

    T& operator*() { return this->node_->value; }

    ListIterator operator--(int) {
      ListIterator temp = *this;
      this->node_ = this->node_->prev;
      return temp;
    }

    ListIterator operator++(int) {
      ListIterator temp = *this;
      this->node_ = this->node_->next;
      return temp;
    }

    friend std::ostream& operator<<(std::ostream& os, const ListIterator& i) {
      os << i;
      return os;
    }
  };

  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator(NodeTwo<T>* node) : ListIterator(node) {}
    ListConstIterator(const ListIterator& obj) : ListIterator(obj) {}
  };

  using iterator = ListIterator;
  using const_iterator = const ListConstIterator;

  list()
      : size_of_list(0),
        top_of_list(nullptr),
        tail_of_list(nullptr),
        current_size(0){};
  ~list() { clear(); }

  list(size_type n) : list() {
    for (size_t i = 0; i < n; ++i) {
      push_back(T());
    }
  }

  list(std::initializer_list<value_type> const& items) : list() {
    for (const auto& item : items) push_back(item);
  }

  void printList() {
    std::cout << "list =" << std::endl;
    NodeTwo<T>* temp = top_of_list;
    while (temp != nullptr) {
      std::cout << temp->value << std::endl;
      temp = temp->next;
    }
  }

  bool empty() { return (current_size == 0); }

  void clear() {
    while (top_of_list != nullptr) {
      pop_front();
    }
  }

  void pop_front() {
    if (empty()) return;
    NodeTwo<T>* temp = top_of_list;
    top_of_list = temp->next;

    if (top_of_list)
      top_of_list->prev = nullptr;
    else
      tail_of_list = nullptr;

    delete temp;
    --current_size;
  }

  void pop_back() {
    if (empty()) throw std::out_of_range("list is empty");
    NodeTwo<T>* temp = tail_of_list;
    tail_of_list = temp->prev;

    if (tail_of_list)
      tail_of_list->next = nullptr;
    else
      top_of_list = nullptr;

    --current_size;
  }

  void push_back(const_reference value) {
    NodeTwo<T>* newNode = new NodeTwo<T>(value);
    if (empty()) {
      top_of_list = newNode;
      tail_of_list = newNode;
    } else {
      tail_of_list->next = newNode;
      newNode->prev = tail_of_list;
      tail_of_list = newNode;
    }
    ++current_size;
  }

  void push_front(const_reference value) {
    NodeTwo<T>* newNode = new NodeTwo<T>(value);
    if (empty()) {
      top_of_list = newNode;
      tail_of_list = newNode;
      newNode->next = nullptr;
      newNode->prev = nullptr;
    } else {
      newNode->next = top_of_list;
      top_of_list->prev = newNode;
      top_of_list = newNode;
    }
    ++current_size;
  }

  const_reference front() { return top_of_list->value; }

  const_reference back() { return tail_of_list->value; }

  iterator begin() { return iterator(top_of_list); }

  const_iterator cbegin() const { return const_iterator(top_of_list); }

  iterator end() { return iterator(tail_of_list->next); }

  const_iterator cend() const { return const_iterator(tail_of_list->next); }

  list(const list& l) : list() {
    NodeTwo<T>* current_l = l.top_of_list;
    while (current_l != nullptr) {
      push_back(current_l->value);
      current_l = current_l->next;
    }
  }

  list(list&& l) : list() {
    if (this != &l) {
      clear();
      size_of_list = l.size_of_list;
      top_of_list = l.top_of_list;
      tail_of_list = l.tail_of_list;
      current_size = l.current_size;

      l.clear();
    }
  }

  bool operator==(const list& l) const {
    if (size_of_list != l.size_of_list) return false;

    iterator it1 = cbegin();
    iterator it2 = l.cbegin();

    while (it1 != cend() && it2 != l.cend()) {
      if (*it1 != *it2) return false;
      ++it1;
      ++it2;
    }

    return true;
  }

  list& operator=(list& l) {
    if (this != &l) {
      clear();
      NodeTwo<T>* current_l = l.top_of_list;
      while (current_l != nullptr) {
        push_back(current_l->value);
        current_l = current_l->next;
      }
    }
    return *this;
  }

  list& operator=(list&& l) {
    if (this != &l) {
      clear();
      size_of_list = l.size_of_list;
      top_of_list = l.top_of_list;
      tail_of_list = l.tail_of_list;
      current_size = l.current_size;

      l.clear();
    }
    return *this;
  }

  size_type size() { return current_size; }

  size_type max_size() {  //?
    if (current_size == 0) return std::numeric_limits<size_type>::max();
    return std::numeric_limits<size_t>::max() / sizeof(T);
  }

  void swap(list& other) {
    NodeTwo<T>* temp = top_of_list;
    top_of_list = other.top_of_list;
    other.top_of_list = temp;

    NodeTwo<T>* temp1 = tail_of_list;
    tail_of_list = other.tail_of_list;
    other.tail_of_list = temp1;

    size_t temp2 = size_of_list;
    size_of_list = other.size_of_list;
    other.size_of_list = temp2;

    size_t temp3 = current_size;
    current_size = other.current_size;
    other.current_size = current_size;
  }

  iterator insert(iterator pos, const_reference value) {
    NodeTwo<T>* newNode = new NodeTwo<T>(value);

    if (empty()) {
      top_of_list = newNode;
      tail_of_list = newNode;
      newNode->next = nullptr;
      newNode->prev = nullptr;
      current_size++;
      return iterator(newNode);
    }

    if (pos == begin()) {
      newNode->next = top_of_list;
      newNode->prev = nullptr;
      top_of_list->prev = newNode;
      top_of_list = newNode;
    } else {
      NodeTwo<T>* current = pos.node_;
      newNode->next = current;

      if (current->prev) current->prev->next = newNode;
      current->prev = newNode;

      if (newNode->next == nullptr) tail_of_list = newNode;
    }
    ++current_size;
    return iterator(newNode);
  }

  void sort() {
    if (empty()) throw std::out_of_range("List is empty");

    bool swapped = true;
    while (swapped) {
      swapped = false;
      for (iterator i = begin(); i != end(); ++i) {
        iterator j = i;
        iterator next = ++j;

        if (next == end()) break;
        if (*i > *next) {
          T temp = *i;
          *i = *next;
          *next = temp;
          swapped = true;
        }
      }
    }
  }

  void unique() {
    NodeTwo<T>* current = top_of_list;
    size_t count = 0;
    while (current) {
      NodeTwo<T>* runner = current->next;
      while (runner) {
        if (current->value == runner->value) {
          if (runner->next) runner->next->prev = runner->prev;
          if (runner->prev) runner->prev->next = runner->next;
          if (runner == top_of_list) top_of_list = runner->next;

          runner = runner->next;
          --current_size;
        } else
          runner = runner->next;
      }
      current = current->next;
    }
  }

  void reverse() {
    if (empty()) throw std::out_of_range("List is empty");
    list<T> temp;
    for (iterator i = begin(); i != end(); ++i) {
      temp.push_front(*i);
    }
    *this = temp;
    temp.clear();
  }

  void merge(list& other) {
    if (empty() && other.empty())
      throw std::out_of_range("Lists are empty");
    else if (empty()) {
      other.sort();
      *this = other;
    } else if (other.empty())
      sort();
    else {
      for (iterator i = begin(); i != end(); ++i) {
        other.push_back(*i);
      }
      other.sort();
      *this = other;
    }
  }

  void erase(iterator pos) {
    if (pos == begin()) {
      pop_front();
    } else {
      iterator pr = begin();
      while (pr.node_ != pos.node_) ++pr;
      if (pr.node_->prev) pr.node_->prev->next = pr.node_->next;
      if (pr.node_->next) pr.node_->next->prev = pr.node_->prev;

      delete pr.node_;
    }
  }

  void splice(const_iterator pos, list& other) {
    if (other.empty()) return;
    list<T> temp;
    for (iterator i = begin(); i != end(); ++i) {
      if (i == pos) {
        for (iterator j = other.begin(); j != other.end(); ++j)
          temp.push_back(*j);
      }
      temp.push_back(*i);
    }
    if (pos == const_iterator(end())) {
      for (iterator j = other.begin(); j != other.end(); ++j)
        temp.push_back(*j);
    }
    clear();
    for (iterator i = temp.begin(); i != temp.end(); ++i) {
      push_back(*i);
    }
    other.clear();
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    for (const auto& arg : {args...}) insert(pos, arg);
    return pos;
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    for (const auto& arg : {args...}) push_back(arg);
  }

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    for (const auto& arg : {args...}) push_front(arg);
  }
};
};  // namespace s21

#endif