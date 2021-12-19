#ifndef GRAPH_LIB_ADDITIONS_H
#define GRAPH_LIB_ADDITIONS_H 1

#include <FL/Fl_Radio_Round_Button.H>
#include <FL/FL_Box.H>
#include "../Graph_lib/GUI.h"
#include "constants.h"

using Address = void *;
using Callback = void (*)(Address, Address); 

namespace Graph_lib
{
  using namespace PlotterLib;

  struct RadioButton : Widget 
  {
    ModesNames mode;

    RadioButton (Graph_lib::Point xy, int w, int h, const std::string& label, ModesNames mode_num, Callback cb)
      : Widget{ xy, w, h, label, cb }
    { mode = mode_num;}

    void attach (Graph_lib::Window& win) override;
    Graph_lib::Window* get_window(){return own;};

  };

  struct TextField : Graph_lib::Widget
  {
    TextField (Point xy, int w, int h, const std::string& label)
      : Widget{ xy, w, h, label, nthg }
    {}

    void attach (Graph_lib::Window& win) override;
    Graph_lib::Window* get_window(){return own;};
  };

  struct Curve : Shape 
  {
    using Shape::Shape;

    void add (Point p)  { Shape::add(p); }
    void draw_lines () const override;
  };

};

#endif