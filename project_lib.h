#ifndef PROJECT_LIB_H
#define PROJECT_LIB_H

#include <iostream>
#include <functional>
#include <vector>

namespace CONSTS
{
  using namespace Graph_lib;
  const int SKALE = 3;
  const Point WIN_SIZE {800, 600};
  const int X = SKALE*30; // X -> X_R
  const int Y_H = SKALE*20;
  const int Y_B = WIN_SIZE.y-SKALE*20;
  const std::vector <int> BUTTON_SIZE {SKALE*40, SKALE*12}; 
  const std::vector <int> MENU_BUTTON_SIZE {SKALE*100, SKALE*12}; 
  const int X_L = X + WIN_SIZE.x-int(2.3*BUTTON_SIZE[0]);
};

class Invalid_input 
{
private:
  std::string e rror_m;

public:
  Invalid_input(std::string error) 
  : error_m {error}
  {}

  const std::string getError () {return error_m;}
};

#endif