#ifndef GUI_H
#define GUI_H 1

#include "../Graph_lib/Window.h"
#include "../Graph_lib/Graph.h"
#include "space_point.h"
#include "Graph_lib_additions.h"

using namespace CONSTS;
using namespace Graph_lib;

struct WidgetSets
{
  int current_mode;
  
  Vector_ref <Widget> mode1;
  Vector_ref <Widget> mode2; 
  Vector_ref <Vector_ref <Widget>> modes;

  WidgetSets();
};


class PlotterWindow : Graph_lib::Window
{
public:
  PlotterWindow (Point xy, int w, int h, const std::string & title);

private:
  Button enter_button;
  Out_box error_outbox;
  RadioButton mode_1; 
  RadioButton mode_2;
  WidgetSets wid_sets;
  Screen screen;

  static void cb_mode(Address wid, Address win);
  static void cb_enter(Address, Address addr);
  void set_mode(Address wid);
  void switch_mode(RadioButton& rb, int num, bool turn);
  void attach_v(Vector_ref <Widget> & v);
  void draw_screen();
  void clear_screen();
};



class Screen
{
private:
  int w;
  int h;
  int skale;
  Graph_lib::Point pos;
  const Graph* G;
  Rectangle field;
  Vector_ref <Line> axis;

public:
  Screen(int ww, int hh, int sk, Graph_lib::Point p);

  const Graph* calc_graph(func F, Range R);
  static const Graph_lib::Point get_projection(SpacePoint p);

  ~Screen() { delete G; }
};


#endif