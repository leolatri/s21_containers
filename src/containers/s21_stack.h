#ifndef __S21_STACK_H__
#define __S21_STACK_H__

#include "s21_node.h"

namespace s21 {

template <typename T>
class stack {
 private:
  Node<T>* top_of_stack;
  size_t size_of_stack;

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  stack() : top_of_stack(nullptr), size_of_stack(0){};
  ~stack() { clear(); }

  stack(const stack& s) : stack() {
    Node<T>* current_s = s.top_of_stack;
    for (size_t i = 0; i < s.size_of_stack; ++i) {
      push(current_s->value);
      current_s = current_s->next;
    }
  }

  stack(stack&& s) {
    if (this != &s) {
      clear();
      size_of_stack = s.size_of_stack;
      top_of_stack = s.top_of_stack;

      s.size_of_stack = 0;
      s.top_of_stack = nullptr;
    }
  }

  stack& operator=(const stack& s) {
    if (this != &s) {
      clear();
      Node<T>* current_s = s.top_of_stack;
      while (current_s != nullptr) {
        push(current_s->value);
        current_s = current_s->next;
      }
    }
    return *this;
  }

  bool operator==(stack& s) {
    if (this->size_of_stack != s.size_of_stack) return false;

    Node<T>* current = top_of_stack;
    Node<T>* current_s = s.top_of_stack;

    for (size_t i = 0; i < size_of_stack; ++i) {
      if (current->value != current_s->value) return false;
      current = current->next;
      current_s = current_s->next;
    }

    return true;
  }

  stack& operator=(stack&& s) {
    if (this != &s) {
      clear();
      size_of_stack = s.size_of_stack;
      top_of_stack = s.top_of_stack;

      s.size_of_stack = 0;
      s.top_of_stack = nullptr;
    }
    return *this;
  }

  stack(std::initializer_list<value_type> const& items) : stack() {
    for (const auto& item : items) {
      push(item);
    }
  }

  void printStack() {
    std::cout << "stack =" << std::endl;
    Node<T>* temp = top_of_stack;
    while (temp != nullptr) {
      std::cout << temp->value << std::endl;
      temp = temp->next;
    }
    delete[] temp;
  }

  void clear() {
    while (top_of_stack != nullptr) {
      pop();
    }
  }

  const_reference top() {
    if (empty()) throw std::invalid_argument("Stack is empty");
    return top_of_stack->value;
  }

  bool empty() { return (size_of_stack == 0); }

  size_type size() { return size_of_stack; }

  void push(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    newNode->next = top_of_stack;
    top_of_stack = newNode;
    size_of_stack++;
  }

  void pop() {
    if (empty()) throw std::out_of_range("Stack is empty");
    Node<T>* temp = top_of_stack;
    top_of_stack = temp->next;
    delete temp;
    --size_of_stack;
  }

  void swap(stack& other) {
    if (this != &other) {
      Node<T>* temp = top_of_stack;
      top_of_stack = other.top_of_stack;
      other.top_of_stack = temp;

      size_t tmp = size_of_stack;
      size_of_stack = other.size_of_stack;
      other.size_of_stack = tmp;
    }
  }

  template <typename... Args>
  void insert_many_front(Args&&... args) {  //?
    for (const auto& arg : {args...}) push(arg);
  }
};
}  // namespace s21

#endif