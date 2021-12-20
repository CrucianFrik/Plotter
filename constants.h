#ifndef CONSTANTS_H
#define CONSTANTS_H 1
#include "../Graph_lib/Graph.h"

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


enum ModesNames
{
  equation, 
  parametric
};

namespace CONSTS
{
  const int SKALE = 3;  //!= Screen::scale
  const int INDENT = SKALE*3;
  const Graph_lib::Point WIN_SIZE {1200, 900};

  const std::vector <int> BUTTON_SIZE {SKALE*40, SKALE*12}; 
  const std::vector <int> MENU_BUTTON_SIZE {SKALE*100, SKALE*12}; 
  
  const int X_L = SKALE*30;
  const int X_R = X_L + WIN_SIZE.x-int(2.3*BUTTON_SIZE[0]);
  const int Y_H = SKALE*20;
  const int Y_B = WIN_SIZE.y-SKALE*20;
  
  const Graph_lib::Point SCREEN_POINT {X_L+MENU_BUTTON_SIZE[0]+3*INDENT, Y_H};
  const int SCREEN_SKALE = 22;
  const int SCREEN_W = WIN_SIZE.x - X_L - SCREEN_POINT.x;
  const int SCREEN_H = SCREEN_W;

  const Range RANGE {-9, 9};
  const Steps STEP {0.25, 0.05, 0.1};
};

#endif