#include "gui.h"

const Point Screen::get_projection( SpacePoint p )
{ 
  Vec3d i {-2, 3, 0};
  i = i/abs(i);

  Vec3d j {-48, -32, 65};
  j = j/abs(j);

  int x = dot(p, i) * skale;
  int y = dot(p, j) * skale;

  return Point( pos.x + h/2 + x, pos.y + w/2 - y);
}
