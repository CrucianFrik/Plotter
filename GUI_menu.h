#ifndef GUI_MENU_H
#define GUI_MENU_H

#include "../Graph_lib/Window.h"
#include "../Graph_lib/Graph.h"

#include "project_lib.h"
#include "widgets.h"

#define DEBUG_OUT(x) std::cout << ": "<< (#x) <<" = "<< (x) << std::endl

using namespace CONSTS;
using namespace Graph_lib;

struct MODES
{
  int current_mode = 0;
  
  Vector_ref <Widget > mode1_wids;
  Vector_ref <Widget> mode2_wids; 
  Vector_ref <Vector_ref <Widget>> modes;


  MODES()
  {
  mode1_wids.push_back(new In_box {Point{X, Y_B - BUTTON_SIZE[1] - SKALE*3},
                                  WIN_SIZE.x-2*BUTTON_SIZE[0], BUTTON_SIZE[1], "f (x, y, z):"});
  mode1_wids.push_back(new TextField {Point{X_L,  Y_B - BUTTON_SIZE[1] - SKALE*3}, 
                                      BUTTON_SIZE[0], BUTTON_SIZE[1], " = 0"});

  mode2_wids.push_back(new In_box {Point{X, Y_B - 3*(BUTTON_SIZE[1] + SKALE*3)},
                                  WIN_SIZE.x-2*BUTTON_SIZE[0], BUTTON_SIZE[1], std::string {"x (t, p, q) = "}});
  mode2_wids.push_back(new In_box {Point{X, Y_B - 2*(BUTTON_SIZE[1] + SKALE*3)},
                                  WIN_SIZE.x-2*BUTTON_SIZE[0], BUTTON_SIZE[1], std::string {"y (t, p, q) = "}});
  mode2_wids.push_back(new In_box {Point{X, Y_B - (BUTTON_SIZE[1] + SKALE*3)},
                                  WIN_SIZE.x-2*BUTTON_SIZE[0], BUTTON_SIZE[1], std::string {"z (t, p, q) = "}});
  
  modes.push_back(mode1_wids);
  modes.push_back(mode2_wids);
  }
};

struct GUI_menu : Graph_lib::Window
{
public:
  GUI_menu (Point xy, int w, int h, const std::string & title);
  void c();

private:
  Button enter_button;
  Out_box error_outbox;
  RadioButton mode_1; 
  RadioButton mode_2;
  MODES m;

  static void cb_mode(Address wid, Address win);
  static void cb_enter(Address, Address addr);
  void set_mode(Address wid);
  void switch_mode(RadioButton& rb, int num, bool turn);
  void attach_v(Vector_ref <Widget> & v);


};

#endif