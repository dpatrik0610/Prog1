/*
    g++ ch13drill.cpp Graph.cpp Window.cpp GUI.cpp Simple_window.cpp -o ch13drill `fltk-config --ldflags --use-images` -std=c++11
*/
#include "../gui/Simple_window.h"
#include "../gui/Graph.h"


int main()
{
    int window_width = 800, window_height = 1000;
    Simple_window win {Point{100,100},window_width,window_height,"Simple Window."};
    // Widow size
    int x_size = win.x_max();
    int y_size = win.y_max();
    // Grid sze
    int x_grid = 100;
    int y_grid = 100;
    // Rectangle size
    int rect_xpos = 100;
    int rect_ypos = 100;

    Lines grid;
    for (int x=x_grid; x < 800; x += x_grid)
        grid.add(Point{x,0},Point{x,y_size});
    for (int y = y_grid; y < 800; y += y_grid)
        grid.add(Point{0,y},Point{x_size,y});
    
    Rectangle rect {Point{rect_xpos,rect_ypos},x_grid,y_grid};
    rect.set_fill_color(Color::red);
    win.attach(rect);
    win.attach(grid);
    win.wait_for_button();
}