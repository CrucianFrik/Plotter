#include "grammar.h"

func get_function(std::string& s)
{
  Token_stream ts {s};
  return expression(ts);
}


func expression(Token_stream& ts)
{
  func left = term(ts);
  Token t = ts.get();
  switch ( t.type() )
  {
    case operation:
      if (t.value() == '+') 
      {
        return left + expression(ts);
      }
      else  // only '-' can be
      {
        return left - expression(ts);
      }

    case end:
      return left;

    default:
      ts.putback(t);
      return left;
  }
}


func term(Token_stream& ts)
{
  func left = subterm(ts);
  Token t = ts.get();
  switch ( t.type() )
  {
    case operation:
      if (t.value() == '*')
      {
        return left * subterm(ts);
      }
      else if (t.value() == '/')
      {
        return left / subterm(ts);
      }
      else
      {
        ts.putback(t);
        return left;
      }
    
    case number:
      throw Token_error("Number in unexpexted place");

    case end:
      return left;

    default:
      ts.putback(t);
      return left;
  }
}


func subterm(Token_stream& ts, bool read_minus)
{
  func left = phrase(ts, read_minus);
  Token t = ts.get();
  switch ( t.type() )
  {
    case end:
      return left;

    case number:
    case operation:
      ts.putback(t);
      return left;

    case brace:
      if (t.value() == ')' or t.value() == ']' or t.value() == '}')
      {
        ts.putback(t);
        return left;
      }
      [[fallthrough]];
    
    case argument:
    case function:
      ts.putback(t);
      return left * subterm(ts, read_minus);       
  }
  throw Token_error("Unexpected token type");
}


func phrase(Token_stream& ts, bool read_minus)
{
  Token t = ts.get();
  if (read_minus and t.type() == operation and t.value() == '-')
  {
    return (-1)*phrase(ts, true);
  }
  
  ts.putback(t);
  func left = primary(ts);
  t = ts.get();
  switch( t.type() )
  {
    case operation:
      if ( t.value() == '^')
      {
        return left ^ subterm(ts);
      }
      else
      { 
        ts.putback(t);
        return left;
      }

    case end:
      return left;

    default:
      ts.putback(t);
      return left;
  }
}


func primary(Token_stream& ts)
{
  Token t = ts.get();
  switch( t.type() )
  {
    case argument:
    case number:
      return t.value();

    case brace:
    {
      if (t.value() == ')' or t.value() == ']' or t.value() == '}')
      {
        ts.putback(t);
        throw Token_error("Primary expected");
      }
      
      switch ( t.value() )
      {
        case '(':
        {
          func f = expression(ts);
          t = ts.get();
          if (t.type() != brace or t.value() != ')')
            throw Token_error("')' expected");
          return f;
        }

        case '[':
        {
          func f = expression(ts);
          t = ts.get();
          if (t.type() != brace or t.value() != ']')
            throw Token_error("']' expected");
          return f;
        }

        case '{':
        {
          func f = expression(ts);
          t = ts.get();
          if (t.type() != brace or t.value() != '}')
            throw Token_error("'}' expected");
          return f;
        }
      }
    }
    
    case function:
    {
      Token s = ts.get();
      if (s.type() != brace or s.value() != '(')
        throw Token_error("'(' expected");
        
      scalar_f g = t.value();
      func f = g( expression(ts) );
 
      s = ts.get();    
      if (s.type() != brace or s.value() != ')')
        throw Token_error("')' expected");
      return f;
    }
           
    default:
      throw Token_error("Primary expected");
  }  
}
