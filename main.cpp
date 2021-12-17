#include "gui_1.h"

int main()
{
	GUI_menu win {Point{100, 100}, CONSTS::WIN_SIZE.x, CONSTS::WIN_SIZE.y, "Canvas"}; 

  gui_main();
  return 0;
}