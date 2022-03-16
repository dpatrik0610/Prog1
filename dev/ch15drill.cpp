#include "../gui/Simple_window.h"
#include "../gui/Graph.h"

//g++ ch15drill.cpp ../gui/Graph.cpp ../gui/Window.cpp ../gui/GUI.cpp ../gui/Simple_window.cpp  -o ../builds/ch15 `fltk-config --ldflags --use-images`
// 
struct Canvas{
    const int x_size = 600;
    const int y_size = 600;
    const int x_orig = winSize_x / 2;
    const int y_orig = winSize_y / 2;
    const Point orig {x_orig,y_orig};
};

struct Functions{
    
}
int main() {
    Canvas canvas;
    // Creating the my window with it's properties.
    
    Simple_window win {Point{100,100},canvas.x_size,canvas.y_size,"Function graphs"};

    constexpr int xlength = xmax-40; // make the axis a bit smaller than the window
    constexpr int ylength = ymax-40;
    constexpr int scale = 20;
    Axis x {Axis::x,Point{20, canvas.y_orig}, xlength, xlength/scale, "one notch == 20"};
    Axis y {Axis::y,Point{canvas.x_orig, ylength+20}, ylength, ylength/scale, "one notch == 20"};
    /*Function s {one,r_min,r_max,orig,n_points,x_scale,y_scale};
    Function s2 {slope,r_min,r_max,orig,n_points,x_scale,y_scale};
    Function s3 {square,r_min,r_max,orig,n_points,x_scale,y_scale};

    win.attach(s);
    win.attach(s2);
    win.attach(s3);*/

    win.wait_for_button();
}