#ifndef OPERATORS_H
#define OPERATORS_H 1

#include <functional>
#include <cmath>

using func = std::function<double(double, double, double)>;

class scalar_f: public std::function<double(double)>
{
public:
  scalar_f (std::function<double(double)> f) 
    : std::function<double(double)> (f)
    {}

  scalar_f () 
    : std::function<double(double)> ()
    {}

  double operator() (double x) const;
  func operator() (func f) const; 
};


func operator+ (func f);
func operator- (func f);
func operator+ (func f1, func f2);
func operator- (func f1, func f2);
func operator* (func f1, func f2);
func operator* (double d, func f);
func operator* (func f, double d);
func operator/ (func f1, func f2);
func operator^ (func f1, func f2);

#endif  //  OPERATORS_H
