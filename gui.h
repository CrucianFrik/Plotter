#ifndef GUI_H
#define GUI_H 1

#include "../Graph_lib/Window.h"

#include "Graph_lib_additions.h"
#include "backend.h"
#define DEBUG_OUT(x) std::cout <<__LINE__<<": "<< (#x) <<" = "<< (x) << std::endl

using namespace Graph_lib;

struct WidgetSets
{
  int current_mode;
  
  Vector_ref <Widget> mode1;
  Vector_ref <Widget> mode2; 
  Vector_ref <Vector_ref <Widget>> modes;

  WidgetSets();
};

class Screen
{
public: //DEBUG: public -> private
  static int w;
  static int h;
  static int skale;
  static Graph_lib::Point pos;

public:
  Graph* G = nullptr;
  Graph_lib::Rectangle field;
  Vector_ref <Line> axis;

  Screen()
    : field {pos, w, h}
  {}

  void calc_graph(func F, Range R);
  static const Graph_lib::Point get_projection(SpacePoint p);

  ~Screen() { delete G; }
};


class PlotterWindow : public Graph_lib::Window
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

  template <typename T>
  void attach_vec(Vector_ref <T> & v);
  template <typename T>
  void detach_vec(Vector_ref <T> & v);
  void hide_vec(Vector_ref <Widget> & v);
  
  void draw_screen();
  void clear_screen();
};


#endif