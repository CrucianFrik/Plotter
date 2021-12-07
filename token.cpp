#include "token.h"


Token Token_stream::get()
{
  if (!buffer.empty())
  {
    Token t = buffer[buffer.size()-1];
    buffer.pop_back();
    return t;
  }

  char ch;
  if (is)
    is.get(ch);    
  else if (is.eof())
    return Token {end};     
  else
    throw Token_error("Incorrect input");

  for(; isspace(ch) and is; is.get(ch) );
  if ( is.eof() )
    return Token {end};

  switch (ch)
  {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
      return Token {operation, ch};

    case '(':
    case ')':
    case '{':
    case '}':
    case '[':
    case ']':
      return Token{brace, ch};

    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '.':
      is.putback(ch);
      double val;
      is >> val;
      return Token {number, func { 
                              [val](double, double, double) -> double
                              { return val; } 
                            }
                   };

    case 'x':
    case 't':
      return Token {argument, func {
                                [](double arg1, double, double) -> double
                                { return arg1; }
                              }
                   };

    case 'y':
    case 's':
      return Token {argument, func {
                                [](double, double arg2, double) -> double
                                { return arg2; }
                              }
                   };

    case 'z':
    case 'q':
      return Token {argument, func {
                                [](double, double, double arg3) -> double
                                { return arg3; }
                              }
                   };

    default:
      if (std::isalpha(ch) or ch == '_')
      {
        std::string name {ch};
        while (is.get(ch) and 
               (std::isalpha(ch) or std::isdigit(ch) or ch == '_'))
          name += ch;
        if (is)
          is.putback(ch);

        if (scalar_funcs.find(name) != scalar_funcs.end())
          return Token {function, scalar_funcs.at(name)};
      }
      throw Token_error("Bad token");
  }
}

