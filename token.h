#ifndef TOKEN_H
#define TOKEN_H 1

#include <vector>
#include <sstream>
#include <unordered_map>
#include "operators.h"
#include "parce.h"

using isstream = std::istringstream;

const std::unordered_map <std::string, scalar_f> scalar_funcs = {
    {"sin",  scalar_f { sin }  },
    {"asin", scalar_f { asin } },
    {"cos",  scalar_f { cos }  },
    {"acos", scalar_f { acos } },
    {"tan",  scalar_f { tan }  },
    {"atan", scalar_f { atan } }
};


enum Token_type
{
  argument,
  number,
  operation,
  brace,
  function,
//  variable,
//  constant,
  end
}; 

class Val_type
{
public:
  Val_type(func f_)       { f = f_; }
  Val_type(char ch_)      { ch = ch_; }
  Val_type(scalar_f s_f_) { s_f = s_f_; }
  Val_type() = default;

  operator char()     { return (*this).ch; }
  operator func()     { return (*this).f; }
  operator scalar_f() { return (*this).s_f; } 

private:  
  func f;
  char ch;
  scalar_f s_f;
};

class Token
{  
public:
  template <typename T>
  Token (Token_type t_, T v)
    : t {t_}, val {v} {}

  Token (Token_type t_)
    : t {t_}, val {} {}

  Token_type type() { return t; }
  Val_type value()  { return val; }

private:
  Token_type t;
  Val_type val;   
};


class Token_stream
{
public:

  Token_stream(std::string input_string) 
  { 
    if (input_string == "")
      throw Token_error("No input");
    is = isstream{ input_string + " " }; 
  }

  Token get();
  void putback(Token t) { buffer.push_back(t); }

private:
  std::vector<Token> buffer{};
  isstream is;
};

#endif    // TOKEN_H
