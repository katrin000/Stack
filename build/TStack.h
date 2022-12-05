#pragma once
#include <iostream>


using namespace std;

template<class T>
class Stack {
  int size;//размер буфера
  int cur;
  T* arr;
  void repackage() {
    int new_size = size * 2 + 5;
    T* tmp = new T[new_size]{};
    for (int i = 0; i <= cur; i++) {
      tmp[i] = arr[i];
    }
    if (size > 0)
      delete[]arr;
    arr = tmp;
    size = new_size;
  }
public:
  Stack(int _size = 1) {
    size = _size; cur = 0;
    arr = new T[size]{};
  }
  Stack(const Stack<T>& q) {
    size = q.size;
    cur = q.cur;
    arr = new T[size]{};
    for (int i = 0; i < cur; i++) {
      arr[i] = q.arr[i];
    }
  }
  Stack(Stack<T>&& q) {
    arr = nullptr;
    cur = size = 0;
    swap(*this, q);
  }
  Stack<T>& operator=(const Stack<T>& q) {
    if (*this == q)
      return *this;
    if (size > 0)
      delete[]arr;
    size = q.size; cur = q.cur;
    arr = new T[size]{};
    for (int i = 0; i < cur; i++) {
      arr[i] = q.arr[i];
    }
    return *this;
  }
  Stack<T>& operator=(Stack<T>&& q) {
    if (*this == q)
      return *this;
    if (size > 0)
      delete[]arr;
    arr = nullptr;
    cur = size = 0;
    swap(*this, q);
    return *this;
  }
  bool is_empty() {
    if (cur == 0)
      return true;
    return false;
  }
  bool is_full() {
    if (cur == size - 1)
      return true;
    return false;
  }
  int get_size() {
    return cur;
  }
  void push(T x) {
    if (this->is_full()) {
      //Делаем перепаковку, увеличиваем память в 2 раза
      repackage();
    }
    arr[cur] = x;
    cur++;
  }
  T top() {
    return arr[cur - 1];
  }
  T pop() {
    if (this->is_empty())
      throw exception();
    T v = arr[cur - 1]; cur--;
    return v;
  }
  ~Stack() {
    if (size > 0)
      delete[]arr;
  }
  friend void swap(Stack<T>& left, Stack<T>& right) {
    swap(left.size, right.size);
    swap(left.arr, right.arr);
    swap(left.cur, right.cur);
  }
  friend ostream& operator<<(ostream& out, Stack<T>& obj) {
    if (obj.is_empty()) {
      out << "Stack is Empty!\n";
      return out;
    }
    for (int i = obj.cur - 1; i >= 0; i--) {
      out << obj.arr[i] << ' ';
    }
    out << '\n';
    return out;
  }
};