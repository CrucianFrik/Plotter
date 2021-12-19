#ifndef WIDGETS_H
#define WIDGETS_H

#include <FL/Fl_Radio_Round_Button.H>
#include <FL/FL_Box.H>
#include "../Graph_lib/GUI.h"

#include "project_lib.h"

using Address = void *;
using Callback = void (*)(Address, Address); 

namespace PlotterLib
{
  enum ModesNames
  {
    equation, 
    parametric
  };
};

namespace Graph_lib
{
  using namespace PlotterLib;

  struct RadioButton : Graph_lib::Widget 
  {
  public:
    Graph_lib::Window* get_window(){return own;};
    ModesNames mode;

    RadioButton (Graph_lib::Point xy, int w, int h, const std::string& label, 
                ModesNames mode_num, Callback cb)
      : Graph_lib::Widget{ xy, w, h, label, cb }
    { 
      mode = mode_num;
    }

    void attach (Graph_lib::Window& win)
    {
      pw = new Fl_Radio_Round_Button{ loc.x, loc.y, width, height, label.c_str() };
      pw->callback (reinterpret_cast<Fl_Callback*>(do_it), &win);
      pw->user_data(this);
      own = &win;
    }

  };

  struct TextField : Graph_lib::Widget
  {
  public: 
    Graph_lib::Window* get_window(){return own;};
    TextField (Graph_lib::Point xy, int w, int h, const std::string& label)
      : Graph_lib::Widget{ xy, w, h, label, nthg }
    {}

    void attach (Graph_lib::Window& win)
    {
      pw = new Fl_Box{ loc.x, loc.y, width, height, label.c_str() };
      pw->callback (reinterpret_cast<Fl_Callback*>(do_it), &win);
      pw->user_data(this);
      own = &win;
    }
  };
};

#endif