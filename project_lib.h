#ifndef PROJECT_LIB_H
#define PROJECT_LIB_H

#include <iostream>
#include <functional>
#include <vector>

struct MyExeption
{
  std::string m_error = "";
  MyExeption(std::string error)
  : m_error(error) {}

  const char* get_error() { return m_error.c_str();}
};

struct Steps
{
  double l;  //Шаг между линиями
  double p;  //Шаг между точками на линии
  double f;  //Шаг для перебора значений третей переменной 
          //при имеющихся двух для нахождения x3 по f(x1, x2)

  Steps(double ll, double pp, double ff)
    :l{ll}, p{pp}, f{ff} 
  {}
};

struct Range
{
  double start;
  double end;

  Range(double s, double e)
    : start{s}, end{e}{}
};


namespace CONSTS
{
  using namespace Graph_lib;
  const int SKALE = 3;
  const int INDENT = SKALE*3;
  const Point WIN_SIZE {1000, 800};
  const int X = SKALE*30; // X == X_R
  const int Y_H = SKALE*20;
  const int Y_B = WIN_SIZE.y-SKALE*20;
  const std::vector <int> BUTTON_SIZE {SKALE*40, SKALE*12}; 
  const std::vector <int> MENU_BUTTON_SIZE {SKALE*100, SKALE*12}; 
  const int X_L = X + WIN_SIZE.x-int(2.3*BUTTON_SIZE[0]);
  
  const Point SCREEN_POINT {X+MENU_BUTTON_SIZE[0]+SKALE*3, Y_H};
  const int SCREEN_SKALE = 1;
  const int SCREEN_W = WIN_SIZE[0] - X - SCREEN_POINT[0];
  const int SCREEN_H = WIN_SIZE[1] - INDENT - SCREEN_POINT[1];
  const Range RANGE {-5, 5};
};

class Invalid_input 
{
private:
  std::string error_m;

public:
  Invalid_input(std::string error) 
  : error_m {error}
  {}

  const std::string getError () {return error_m;}
};

bool isnan(double n)
{
  return (n != n);
}

#endif