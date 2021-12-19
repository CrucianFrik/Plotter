class Screen
{
private:
  int w;
  int h;
  int skale;
  Graph_lib::Point pos;
  
  Vector_ref <Open_polyline> elements;

public:
  Screen(int ww, int hh, int sk, Graph_lib::Point p)
    : w{ww}, h{hh}, skale{sk}, pos{p}
  {
    //
  }

  void get_graph(func F, Range R)
  {
    Graph G{F, R};

    

  }

  static const Graph_lib::Point get_projection(SpacePoint p)
  {
    /**/
  }

};
