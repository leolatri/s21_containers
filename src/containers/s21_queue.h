#ifndef __S21_QUEUE_H__
#define __S21_QUEUE_H__

#include "s21_node.h"

namespace s21 {

template <typename T>
class queue {
 private:
  Node<T>* top_of_queue;
  Node<T>* tail_of_queue;
  size_t size_of_queue;

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  queue() : top_of_queue(nullptr), tail_of_queue(nullptr), size_of_queue(0){};
  ~queue() { clear(); }

  queue(const queue& q)
      : size_of_queue(0), tail_of_queue(nullptr), top_of_queue(nullptr) {
    Node<T>* current_q = q.top_of_queue;
    while (current_q != nullptr) {
      push(current_q->value);
      current_q = current_q->next;
    }
  }

  queue(queue&& q) {
    if (this != &q) {
      clear();
      size_of_queue = q.size_of_queue;
      top_of_queue = q.top_of_queue;
      tail_of_queue = q.tail_of_queue;

      q.size_of_queue = 0;
      q.top_of_queue = nullptr;
      q.tail_of_queue = nullptr;
    }
  }

  queue& operator=(const queue& q) {
    if (this != &q) {
      clear();
      Node<T>* current_q = q.top_of_queue;
      while (current_q != nullptr) {
        push(current_q->value);
        current_q = current_q->next;
      }
    }
    return *this;
  }

  bool operator==(queue& other) {
    if (this->size_of_queue != other.size_of_queue) return false;

    Node<T>* current = top_of_queue;
    Node<T>* current_q = other.top_of_queue;

    for (size_t i = 0; i < size_of_queue; ++i) {
      if (current->value != current_q->value) return false;
      current = current->next;
      current_q = current_q->next;
    }

    return true;
  }

  queue& operator=(queue&& q) {
    if (this != &q) {
      clear();

      top_of_queue = q.top_of_queue;
      tail_of_queue = q.tail_of_queue;
      size_of_queue = q.size_of_queue;

      q.top_of_queue = nullptr;
      q.tail_of_queue = nullptr;
      q.size_of_queue = 0;
    }
    return *this;
  }

  queue(std::initializer_list<value_type> const& items) : queue() {
    for (const auto& item : items) push(item);
  }

  void printQueue() {
    std::cout << "queue =" << std::endl;
    Node<T>* temp = top_of_queue;
    while (temp != nullptr) {
      std::cout << temp->value << std::endl;
      temp = temp->next;
    }
  }

  void clear() {
    while (top_of_queue != nullptr) {
      pop();
    }
  }

  const_reference front() {
    if (empty()) throw std::invalid_argument("Queue is empty");
    return top_of_queue->value;
  }

  const_reference back() {
    if (empty()) throw std::invalid_argument("Queue is empty");
    return tail_of_queue->value;
  }

  bool empty() { return (size_of_queue == 0); }

  size_type size() { return size_of_queue; }

  void push(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (empty()) {
      top_of_queue = newNode;
    } else {
      tail_of_queue->next = newNode;
    }
    tail_of_queue = newNode;
    ++size_of_queue;
  }

  void pop() {
    if (empty()) throw std::out_of_range("queue is empty");
    Node<T>* temp = top_of_queue;
    top_of_queue = temp->next;
    delete temp;
    --size_of_queue;
  }

  void swap(queue& other) {
    if (this != &other) {
      Node<T>* temp = top_of_queue;
      top_of_queue = other.top_of_queue;
      other.top_of_queue = temp;

      Node<T>* temp_1 = tail_of_queue;
      tail_of_queue = other.tail_of_queue;
      other.tail_of_queue = temp_1;

      size_t tmp = size_of_queue;
      size_of_queue = other.size_of_queue;
      other.size_of_queue = tmp;
    }
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    for (const auto& arg : {args...}) push(arg);
  }
};
};  // namespace s21

#endif