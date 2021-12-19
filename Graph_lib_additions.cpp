#include "Graph_lib_additions.h"

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
      if (fill_color().visibility())
      {
        fl_color (fill_color().as_int());
        fl_begin_complex_polygon();
        for(int i = 0; i < number_of_points(); ++i)
        {
          fl_point (point(i).x, point(i).y);
        }
        fl_end_complex_polygon();
        fl_color (color().as_int());
      }

      if (color().visibility())
        Shape::draw_lines();
    }