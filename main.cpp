#include "gui.h"
#include <iostream>

int main()
try
{
    PlotterWindow win {Point{100, 100}, CONSTS::WIN_SIZE.x, CONSTS::WIN_SIZE.y, "Plotter"}; 

    Graph_lib::gui_main();
    return 0;
}
catch (std::exception &e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}
catch (...)
{
    std::cerr << "unknown error" << std::endl;
    return 2;
}
