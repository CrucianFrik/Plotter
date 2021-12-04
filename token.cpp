#include "token.h"


template <typename T>
T Token::get_value()
{
  switch (type)
  {
    case argument:
    case number:
      return *(static_cast<func*>(value));

    case operation:
    case brace:
      return *(static_cast<char*>(value));

    case function:
      return *(static_cast<scalar_f*>(value));

    case end:
      throw Token_error("No value for 'end' type");

    default:
      throw Token_error("Invalid Token type");
  }
}


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
    return Token {end, 0};
  else
    throw Token_error("Incorrect input");

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
                            { return val; } }
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

