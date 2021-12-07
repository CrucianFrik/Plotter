#include "operators.h"


func operator+ (func f1, func f2)
{
  return func {
    [f1, f2](double x, double y, double z) -> double
    { 
      return f1(x, y, z) + f2(x, y, z);
    }
  };
}


func operator- (func f1, func f2)
{
  return func {
    [f1, f2](double x, double y, double z) -> double
    { 
      return f1(x, y, z) - f2(x, y, z);
    }
  };
}


func operator* (func f1, func f2)
{
  return func {
    [f1, f2](double x, double y, double z) -> double
    { 
      return f1(x, y, z) * f2(x, y, z);
    }
  };
}


func operator*(double d, func f)
{
  return func {
    [d, f](double x, double y, double z) -> double
    {
      return d*f(x, y, z);
    }
  };
}


func operator/ (func f1, func f2)
{
  return func {
    [f1, f2](double x, double y, double z) -> double
    { 
      return f1(x, y, z) / f2(x, y, z);
    }
  };
}


func operator^ (func f1, func f2)
{
  return func {
    [f1, f2](double x, double y, double z) -> double
    { 
      return std::pow( f1(x, y, z), f2(x, y, z) );
    }
  };
}


double scalar_f::operator() (double x) const
{
  return std::function<double(double)>::operator() (x);
};


func scalar_f::operator() (func f) const
{
  return func {
    [s_f = *this, f](double x, double y, double z) -> double
    {
      return s_f( f(x, y, z) );
    }
  };
}

