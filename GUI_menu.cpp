#include <iostream>
#include <functional>

#include "GUI_menu.h"

#define DEBUG_OUT(x) std::cout << ": "<< (#x) <<" = "<< (x) << std::endl

using namespace Graph_lib;
using namespace CONSTS;


GUI_menu::GUI_menu (Point xy, int w, int h, const std::string & title)
  : 
  Window{ xy, w, h, title }, 
  
  enter_button{Point{X, Y_B}, BUTTON_SIZE[0], 
              BUTTON_SIZE[1], "enter", cb_enter },

  mode_1 {Point{X, Y_H}, MENU_BUTTON_SIZE[0], MENU_BUTTON_SIZE[1], 
          "Standart input [F(x, y, z) = 0]", PlotterLib::equation, cb_mode},
  
  mode_2 {Point{X, Y_H + BUTTON_SIZE[1] + SKALE*3}, MENU_BUTTON_SIZE[0], 
          MENU_BUTTON_SIZE[1], "Parametric input [x(t) = 0; y(t) = 0; z(t) = 0]", 
          PlotterLib::parametric, cb_mode},

  error_outbox {Point {X, Y_H + 2*(BUTTON_SIZE[1] + SKALE*3)}, 
                MENU_BUTTON_SIZE[0], MENU_BUTTON_SIZE[1]*2, ""},

  screen {SCREEN_W, SCREEN_H, SCREEN_SKALE, SCREEN_POINT, this},

  wid_sets{}

{

  attach(enter_button);
  attach(error_outbox); 
  error_outbox.hide();
  attach(mode_1);
  attach(mode_2);

  for (int i = 0; i < wid_sets.modes.size(); ++i)
  { attach_vec(wid_sets.modes[i]); }

  switch_mode(mode_1, 0, 1);
}


void GUI_menu::attach_vec(Vector_ref <Widget> & v)
{
  for (int j = 0; j < v.size(); ++j)
    {
      attach(v[j]);
      v[j].hide();
    }
}


void GUI_menu::cb_enter(Address, Address addr)
{
  GUI_menu& window = reference_to<GUI_menu>(addr);
  try
  {
    window.error_outbox.hide();

    std::string f_text;
    if (window.wid_sets.current_mode == PlotterLib::equation)
    {
      f_text = (static_cast<In_box*> (&window.wid_sets.modes[PlotterLib::equation][0])) -> get_string();  // std::string -> std::function
      screen.draw_graph(/*parser(f_text)*/, RANGE);
      
      std::cout << f << std::endl;
      if (f == "error") { throw Invalid_input("test"); }
    
    }

    if (window.wid_sets.current_mode == PlotterLib::parametric)
    {

      //parametric input processing

      /*
      std::vector <std::string> F; // <std::string> -> <std::function>
      for (int i = 0; i < 3; ++i)
      {
        f_text = (static_cast<In_box*> (&window.wid_sets.modes[PlotterLib::equation][i])) -> get_string();
        F.push_back(f);
        std::cout << f << std::endl;
      
      }
      */
    }
  }

  catch (Invalid_input& e)
  {
    std::cout << e.getError() << std::endl;
    window.error_outbox.put("Invalid input! " + e.getError());
    window.error_outbox.show();
  }
}


void GUI_menu::cb_mode(Address wid, Address win) 
{
  GUI_menu& window = reference_to<GUI_menu>(win);
  window.set_mode(wid);
}


void GUI_menu::switch_mode(RadioButton& rb, int num, bool turn)
{
  GUI_menu& window = reference_to<GUI_menu>(rb.get_window());

  if (turn)
  {
    for (int j = 0; j < window.wid_sets.modes[num].size(); ++j)
    { window.wid_sets.modes[num][j].show(); }
  }
  else
  {
    for (int j = 0; j < window.wid_sets.modes[num].size(); ++j)
    { window.wid_sets.modes[num][j].hide(); }
  }
}


void GUI_menu::set_mode(Address wid)
{
  Fl_Widget& w = reference_to<Fl_Widget>(wid);
  RadioButton& rb = reference_to<RadioButton>(w.user_data());
  GUI_menu& window = reference_to<GUI_menu>(rb.get_window());

  switch_mode(rb, window.wid_sets.current_mode, 0);
  switch_mode(rb, rb.mode, 1);
  Fl::redraw();

  window.wid_sets.current_mode = rb.mode;
}