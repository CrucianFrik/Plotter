#include <iostream>
#include <functional>
#include "gui.h"
#include "parse.h"


WidgetSets::WidgetSets()
{
mode1.push_back(new In_box {Point{X_L, Y_B - BUTTON_SIZE[1] - SKALE*3},
                                WIN_SIZE.x-2*BUTTON_SIZE[0], BUTTON_SIZE[1], "f (x, y, z):"});
mode1.push_back(new TextField {Point{X_R,  Y_B - BUTTON_SIZE[1] - SKALE*3}, 
                                    BUTTON_SIZE[0], BUTTON_SIZE[1], " = 0"});

mode2.push_back(new In_box {Point{X_L, Y_B - 3*(BUTTON_SIZE[1] + SKALE*3)},
                                WIN_SIZE.x-2*BUTTON_SIZE[0], BUTTON_SIZE[1], std::string {"x (t, p, q) = "}});
mode2.push_back(new In_box {Point{X_L, Y_B - 2*(BUTTON_SIZE[1] + SKALE*3)},
                                WIN_SIZE.x-2*BUTTON_SIZE[0], BUTTON_SIZE[1], std::string {"y (t, p, q) = "}});
mode2.push_back(new In_box {Point{X_L, Y_B - (BUTTON_SIZE[1] + SKALE*3)},
                                WIN_SIZE.x-2*BUTTON_SIZE[0], BUTTON_SIZE[1], std::string {"z (t, p, q) = "}});

modes.push_back(mode1);
modes.push_back(mode2);
}


PlotterWindow::PlotterWindow (Point xy, int w, int h, const std::string & title)
  : 
  Window{ xy, w, h, title }, 
  
  enter_button{Point{X_L, Y_B}, BUTTON_SIZE[0], 
              BUTTON_SIZE[1], "enter", cb_enter },

  mode_1 {Point{X_L, Y_H}, MENU_BUTTON_SIZE[0], MENU_BUTTON_SIZE[1], 
          "Standart input [F(x, y, z) = 0]", PlotterLib::equation, cb_mode},
  
  mode_2 {Point{X_L, Y_H + BUTTON_SIZE[1] + SKALE*3}, MENU_BUTTON_SIZE[0], 
          MENU_BUTTON_SIZE[1], "Parametric input [x(t) = 0; y(t) = 0; z(t) = 0]", 
          PlotterLib::parametric, cb_mode},

  error_outbox {Point {X_L, Y_H + 2*(BUTTON_SIZE[1] + SKALE*3)}, 
                MENU_BUTTON_SIZE[0], MENU_BUTTON_SIZE[1]*2, ""},

  screen {SCREEN_W, SCREEN_H, SCREEN_SKALE, SCREEN_POINT},

  wid_sets{}
{
  wid_sets.current_mode = 0;

  attach(enter_button);
  attach(mode_1);
  attach(mode_2);

  attach(error_outbox); 
  error_outbox.hide();

  for (int i = 0; i < wid_sets.modes.size(); ++i)
  {
    attach_vec(wid_sets.modes[i]); 
    hide_vec(wid_sets.modes[i]); 
  }

  switch_mode(mode_1, wid_sets.current_mode, 1);
}


template <typename T>
void PlotterWindow::attach_vec(Vector_ref <T> & v)
{
  for (int j = 0; j < v.size(); ++j)
    {
      attach(v[j]);
    }
}

template <typename T>
void PlotterWindow::detach_vec(Vector_ref <T> & v)
{
  for (int j = 0; j < v.size(); ++j)
    {
      detach(v[j]);
    }
}

void PlotterWindow::hide_vec(Vector_ref <Widget> & v)
{
  for (int j = 0; j < v.size(); ++j)
    {
      v[j].hide();
    }
}


void PlotterWindow::cb_enter(Address, Address addr)
{
  PlotterWindow& window = reference_to<PlotterWindow>(addr);
  try
  {
    window.error_outbox.hide();

    std::string f_text;
    if (window.wid_sets.current_mode == PlotterLib::equation)
    {
      f_text = (static_cast<In_box*> (&window.wid_sets.modes[PlotterLib::equation][0])) -> get_string(); 
      window.screen.calc_graph(get_function(f_text), RANGE);
      window.clear_screen();
      window.draw_screen();
    }

    if (window.wid_sets.current_mode == PlotterLib::parametric)
    {
      /*...*/
    }
  }

  catch (Token_error& e)
  {
    window.error_outbox.put("Invalid input!\n" + e.what());
    window.error_outbox.show();
  }
}

void PlotterWindow::clear_screen()
{
  detach(screen.field);
  detach_vec(screen.axis);
  for (int i = 0; i < G.figures.size(); ++i)
    detach(G.figures[i].line);
}

void PlotterWindow::draw_screen()
{
  attach(screen.field);
  attach_vec(screen.axis);
  for (int i = 0; i < G.figures.size(); ++i)
    attach(G.figures[i].line);
}

void PlotterWindow::cb_mode(Address wid, Address win) 
{
  PlotterWindow& window = reference_to<PlotterWindow>(win);
  window.set_mode(wid);
}


void PlotterWindow::switch_mode(RadioButton& rb, int mode_num, bool turn)
{
  PlotterWindow& window = reference_to<PlotterWindow>(rb.get_window());

  if (turn)
  {
    for (int j = 0; j < window.wid_sets.modes[mode_num].size(); ++j)
    { window.wid_sets.modes[mode_num][j].show(); }
  }
  else
  {
    for (int j = 0; j < window.wid_sets.modes[mode_num].size(); ++j)
    { window.wid_sets.modes[mode_num][j].hide(); }
  }
}


void PlotterWindow::set_mode(Address wid)
{
  Fl_Widget& w = reference_to<Fl_Widget>(wid);
  RadioButton& rb = reference_to<RadioButton>(w.user_data());
  PlotterWindow& window = reference_to<PlotterWindow>(rb.get_window());

  switch_mode(rb, window.wid_sets.current_mode, 0);
  switch_mode(rb, rb.mode, 1);
  Fl::redraw();

  window.wid_sets.current_mode = rb.mode;
}

Screen::Screen(int ww, int hh, int sk, Graph_lib::Point p);
    : w{ww}, h{hh}, skale{sk}, pos{p},
    Rectangle field {pos, w, h}
{}

const Graph* Screen::calc_graph(func F, Range R)
{
  axis = Vector_ref <Line>;
  axis.push_back(Line(get_projection(SpacePoint{0, 0, 0}), get_projection(SpacePoint{R.end, 0, 0})))
  axis.push_back(Line(get_projection(SpacePoint{0, 0, 0}), get_projection(SpacePoint{0, R.end, 0})))
  axis.push_back(Line(get_projection(SpacePoint{0, 0, 0}), get_projection(SpacePoint{0, 0, R.end})))
  const Graph* G = new Graph{CalcFunction {F, R}, R};
}


