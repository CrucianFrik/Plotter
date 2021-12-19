#include "PlotterWindow.h"

int main()
{
    PlotterWindow win {Point{100, 100}, CONSTS::WIN_SIZE.x, CONSTS::WIN_SIZE.y, "Plotter"}; 

    gui_main();
    return 0;
}