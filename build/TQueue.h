#pragma once
#pragma once
#include <iostream>

using namespace std;

template<class T>
class Queue {
  int size;//размер буфера
  int start;
  int end;
  T* arr;
  int next(int i) { return (i + 1) % size; }
  int next(int i, int j) { return (i + j) % size; }
  void repackage() {
    int new_size = size * 2 + 5;
    T* tmp = new T[new_size]{};
    int index = 1;
    for (int i = start; i != next(end); i = next(i)) {
      tmp[index] = arr[i];
      index++;
    }
    if (size)
      delete[]arr;
    arr = tmp;
    end = size - 1;
    start = 1;
    size = new_size;
  }
public:
  Queue(int _size = 1) {
    size = _size;
    end = 0;
    start = next(end);
    arr = new T[size]{};
  }
  Queue(const Queue<T>& q) {
    size = q.size;
    end = q.end;
    start = q.start;
    arr = new T[size]{};
    for (int i = start; i != next(end); i++) {
      arr[i] = q.arr[i];
    }
  }
  Queue(Queue<T>&& q) {
    arr = nullptr;
    start = end = size = 0;
    swap(*this, q);
  }
  Queue<T>& operator=(const Queue<T>& q) {
    if (*this == q)
      return *this;
    if (size > 0)
      delete[]arr;
    size = q.size;
    end = q.end;
    start = q.start;
    arr = new T[size]{};
    for (int i = start; i != next(end); i++) {
      arr[i] = q.arr[i];
    }
    return *this;
  }
  Queue<T>& operator=(Queue<T>&& q) {
    if (*this == q)
      return *this;
    if (size > 0)
      delete[]arr;
    arr = nullptr;
    start = end = size = 0;
    swap(*this, q);
    return *this;
  }
  int get_size() {
    if (is_empty())
      return 0;
    if (end < start) {
      return  size - start + end + 1;
    }
    else {
      return end - start + 1;
    }
  }
  bool is_empty() {
    if (next(end) == start)
      return true;
    return false;
  }
  bool is_full() {
    if (next(next(end)) == start)
      return true;
    return false;
  }
  void push(T x) {
    if (this->is_full()) {
      //Делаем перепаковку, увеличиваем память в 2 раза
      repackage();
    }
    end = next(end);
    arr[end] = x;
  }
  T top() {
    return arr[end];
  }
  T pop() {
    if (this->is_empty())
      throw exception();
    T v = arr[start];
    start = next(start);
    return v;
  }
  ~Queue() {
    if (size > 0)
      delete[]arr;
  }
  friend void swap(Queue<T>& left, Queue<T>& right) {
    swap(left.size, right.size);
    swap(left.start, right.start);
    swap(left.end, right.end);
    swap(left.arr, right.arr);
  }
  friend ostream& operator<<(ostream& out, Queue<T>& obj) {
    if (obj.is_empty()) {
      out << "Queue is Empty!\n";
      return out;
    }
    for (int i = obj.start; i != obj.next(obj.end); i = obj.next(i)) {
      out << obj.arr[i] << ' ';
    }
    out << '\n';
    return out;
  }
};