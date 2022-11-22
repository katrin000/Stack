#pragma once
#pragma once
#include<string>
#include<iostream>
#include<algorithm>
#include <vector>
#include "TQueue.h"
#include "TStack.h"
#include <map>
using namespace std;

enum TypeElement {
  none,
  Operation,
  number
  //function?
  //float number?
};

int get_priority_operation(string c) {
  if (c == "(")
    return -1;
  if (c == ")")
    return -2;
  if (c == "*" || c == "/")
    return 2;
  if (c == "+" || c == "-")
    return 1;
  return 0;
}

class Lexema {
  TypeElement type;
  string s;
public:
  Lexema(string _s = "", TypeElement _type = none) {
    type = _type;
    s = _s;
  }
  string get_string() {
    return s;
  }
  TypeElement get_type() {
    return type;
  }

  friend ostream& operator << (ostream& out, Lexema& p) {
    out << "{" << p.s << ", ";
    if (p.type == Operation) {
      out << "operation";
    }
    else if (p.type == number) {
      out << "number";
    };
    out << "}";
    out << "\n";
    return out;
  }
};

double calculate(vector<Lexema>& t) {
  //подается на вход обратная польская запись
  Stack<double>stack;
  for (Lexema& l : t) {
    if (l.get_type() == Operation) {
      double v1 = stack.pop();
      double v2 = stack.pop();
      if (l.get_string() == "+") {
        stack.push(v2 + v1);
      }
      else if (l.get_string() == "-") {
        stack.push(v2 - v1);
      }
      else if (l.get_string() == "*") {
        stack.push(v2 * v1);
      }
      else {
        stack.push(v2 / v1);
      }
    }
    else {
      int val = stoi(l.get_string());
      stack.push(val);
    }
  }
  return stack.pop();
}

vector<Lexema> get_postfix(Queue<Lexema> operands) {
  vector<Lexema>ans;
  Stack<Lexema>stack;
  while (!operands.is_empty()) {
    Lexema t = operands.pop();
    if (t.get_type() == number) {
      ans.push_back(t);
    }
    else {
      int priority = get_priority_operation(t.get_string());
      if (priority == -1) {
        //встретили открывающую скобку
        stack.push(t);
        continue;
      }
      while (!stack.is_empty()) {
        Lexema tmp = stack.top();
        int tmp_priority = get_priority_operation(tmp.get_string());
        if (priority == -2 && tmp_priority == -1) {
          //если встретили закрывающую, то вычищаем все символы из стека до открывающей
          stack.pop();
          break;
        }
        else if (tmp_priority == -1)
          break;
        string tmp_str = tmp.get_string();
        if (tmp_priority >= priority) {
          ans.push_back(tmp);
          stack.pop();
        }
        else
          break;
      }
      if (priority != -2)
        stack.push(t);
    }
  }
  while (!stack.is_empty()) {
    Lexema tmp = stack.pop();
    int tmp_priority = get_priority_operation(tmp.get_string());
    if (tmp_priority > 0) {
      //добавляем все символы из стека, которые не равны ( или )
      ans.push_back(tmp);
    }
  }
  return ans;
}
Queue<Lexema> parser(string in) {
  //стандартная версия парсера для чисел и операций
  Queue<Lexema>ans;
  int state = 0;
  string tmp = "";
  //Добавляем пробел, чтобы корректно обработался ввод строки в цикле
  in += ' ';
  string operation = "(/*+-)";
  string separator = " /n/t";
  for (char c : in) {
    switch (state)
    {
    case 0:
      //операция
      if (c >= '0' && c <= '9') {
        tmp = c;
        state = 1;
        break;
      }
      if (count(operation.begin(), operation.end(), c) == 1) {
        //встретился символ с операции
        tmp = c;
        Lexema l(tmp, Operation);
        ans.push(l);
        tmp = "";
        break;
      }
    case 1:
      if (c >= '0' && c <= '9') {
        tmp += c;
        break;
      }
      if (count(operation.begin(), operation.end(), c) == 1) {
        //встретился символ с операции
        Lexema l(tmp, number);
        ans.push(l);
        tmp = c;
        Lexema t(tmp, Operation);
        ans.push(t);
        state = 0;
        tmp = "";
        break;
      }
      if (count(separator.begin(), separator.end(), c) == 1) {
        //встретился сепаратор
        if (tmp == "")break;
        Lexema l(tmp, number);
        ans.push(l);
        tmp = "";
        state = 0;
        break;
      }
    }
  }
  return ans;
}