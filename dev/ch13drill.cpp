/*
g++ ch13drill.cpp ../gui/Graph.cpp ../gui/Window.cpp ../gui/GUI.cpp ../gui/Simple_window.cpp  -o ../builds/ch13 `fltk-config --ldflags --use-images`
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
    // Grid size (Width (x), Height (y))
    int grid_ww = 100;
    int grid_hh = 100;
    // Rectangle position
    int rect_xpos = 100;
    int rect_ypos = 100;
    // Making an 800x800 grid, line by line at x and y.

    Lines grid;
    for (int x=grid_ww; x < 800; x += grid_ww)
        grid.add(Point{x,0},Point{x,y_size});
    for (int y = grid_hh; y < 800; y += grid_hh)
        grid.add(Point{0,y},Point{x_size,y});
        // Basically, Vector_ref simulates a vector of references. (Book page: 811)
        Vector_ref<Rectangle> rectangles;
        for (int i = 0; i < 8; ++i) {
            //Adding a rectangle to the vector at point 100, 200... with the size of each grid ww, hh.
            rectangles.push_back(new Rectangle{Point{i * rect_xpos, i * rect_ypos}, grid_ww, grid_hh});
            rectangles[rectangles.size() - 1].set_fill_color(Color::red);
            win.attach(rectangles[rectangles.size() - 1]);
        }
    // putting on 3 images: 
    Image im1 {Point{200, 0}, "smile.jpg"};
    Image im2 {Point{400,200}, "smile.jpg"};
    Image im3 {Point{600,400}, "smile.jpg"};

    win.attach(grid);
    win.attach(im1);
    win.attach(im2);
    win.attach(im3);
    win.wait_for_button();

    // Creating a moveable Image:
    // Since its an 8 by 8 grid, I set the position of each image as the for loop increases * 100 (grid's width and height)
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            Image movingIm{Point{j * grid_ww, i * grid_hh}, "smile2.jpg"};
            win.attach(movingIm);
            win.wait_for_button();
        }
    }

    win.wait_for_button();
}