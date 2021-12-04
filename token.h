#ifndef TOKEN_H
#define TOKEN_H 1

#include <cmath>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "parce.h"

using isstream = std::istringstream;

std::unordered_map <std::string, scalar_f> scalar_funcs = {
    {"sin",  scalar_f(sin)},
    {"asin", scalar_f(asin)},
    {"cos",  scalar_f(cos)},
    {"acos", scalar_f(acos)},
    {"tan",  scalar_f(tan)},
    {"atan", scalar_f(atan)}
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

class Token
{  
public:
  template <typename T>
  Token (Token_type t, T v)
  { 
    type = t; 
    value = new T {v}; 
  } 

  template <typename T>
  T get_value();

  ~Token() { delete value; }
private:
  Token_type type;
  void* value;   
};


class Token_stream
{
public:

  Token_stream(std::string input_string) { is = isstream{input_string}; }

  Token get();
  void putback(Token t) { buffer.push_back(t); }

private:
  std::vector<Token> buffer{};
  isstream is;
};

#endif    // TOKEN_H
