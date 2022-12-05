#pragma once
#pragma once
#include "Lexema.h"
class Exepcion {
public:
  virtual void show() = 0;
};

class Unknow_symbol :public Exepcion {
  int pos;
  char c;
public:
  Unknow_symbol(char _c = '$', int _pos = 0) {
    pos = _pos;
    c = _c;
  }
  void show() {
    cout << "unknown symbol " << "'" << c << "'" << '\n' << "at position:" << pos << '\n';
  }
};

class LexExepcion :public Exepcion {
protected:
  Lexema lex;
};

class BracketExepcion :public LexExepcion {
public:
  void show() {
    cout << "Incorrect brackets at position:" << lex.get_pos() << '\n';
  }
};