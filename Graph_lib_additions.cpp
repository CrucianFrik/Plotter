#include "Graph_lib_additions.h"

namespace Graph_lib
{

void RadioButton::attach (Graph_lib::Window& win)
{
  pw = new Fl_Radio_Round_Button{ loc.x, loc.y, width, height, label.c_str() };
  pw->callback (reinterpret_cast<Fl_Callback*>(do_it), &win);
  pw->user_data(this);
  own = &win;
}

void TextField::attach (Graph_lib::Window& win)
{
  pw = new Fl_Box{ loc.x, loc.y, width, height, label.c_str() };
  pw->callback (reinterpret_cast<Fl_Callback*>(do_it), &win);
  pw->user_data(this);
  own = &win;
}

void Curve::draw_lines () const
{
  for (int i = 0; i < points.size(); ++i)
    points[i].draw_lines();
}

}