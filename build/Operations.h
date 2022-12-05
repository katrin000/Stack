#pragma once
#pragma once
#include <string>
using namespace std;
class Operations {
public:
  virtual double calc(double x, double y) = 0;
};

class adding :public Operations {
public:
  double calc(double x, double y) {
    return x + y;
  }
};

class subtracting :public Operations {
public:
  double calc(double x, double y) {
    return x - y;
  }
};

class multiplication :public Operations {
public:
  double calc(double x, double y) {
    return x * y;
  }
};

class division :public Operations {
public:
  double calc(double x, double y) {
    return x / y;
  }
};

class exponentiation :public Operations {
public:
  double calc(double x, double y) {
    int n = y;
    if (n != y || y < 0) {
      //возведение в степень только если степень целочисленная и не отрицательная
      throw - 1;
    }
    double res = 1;
    while (n) {
      if (n & 1) {
        res *= x;
        n--;
      }
      else {
        x *= x;
        n >>= 1;
      }
    }
    return res;
  }
};

Operations* get_operations(string t) {
  if (t == "+")
    return new adding();
  if (t == "-")
    return new subtracting();
  if (t == "*")
    return new multiplication();
  if (t == "/")
    return new division();
  if (t == "^")
    return new exponentiation();
}