#include "../../gui/Simple_window.h"
#include "../../gui/Graph.h"

//g++ ch15drill.cpp ../../gui/Graph.cpp ../../gui/Window.cpp ../../gui/GUI.cpp ../../gui/Simple_window.cpp  -o ../builds/ch15 `fltk-config --ldflags --use-images`

struct Canvas {
public:
    const Point startPoint{500,1000};
    const string label = "Function graphs";
    int x_size = 600;
    const int y_size = 600;
    const int x_orig = x_size / 2;
    const int y_orig = y_size / 2;
    const Point orig {x_orig,y_orig};
};

struct myAxis {
    Canvas canvas;
    const int xlength = 400;
    const int ylength = 400;
    const double scale = 20;
    Axis x {Axis::x, Point{20, canvas.y_orig}, xlength, xlength/scale, "1 == 20 pixels"};
    Axis y {Axis::y, Point{canvas.x_orig, ylength+20}, ylength, ylength/scale, "1 == 20 pixels"};
};

struct myFunctions {
private:
    const double rangeMin = -10;
    const double rangeMax = 11;
    const int n_points = 400;
    Canvas canvas;
    myAxis myax;
public:
    Function one {[] (double x) -> double { return 1; }, rangeMin, rangeMax, canvas.orig, n_points, myax.scale, myax.scale};
    Function slope {[] (double x) -> double { return x / 2; }, rangeMin, rangeMax, canvas.orig, n_points, myax.scale, myax.scale};
    Function square {[] (double x) -> double { return x * x; }, rangeMin, rangeMax, canvas.orig, n_points, myax.scale, myax.scale};
    Function sloping_cos {[] (double x) -> double { return cos(x) + x / 2; }, rangeMin, rangeMax, canvas.orig, n_points, myax.scale, myax.scale};
};

int main() {
    Canvas canvas;
    myAxis ax;
    myFunctions myf;
    // Creating the my window with it's properties.
    Simple_window win {canvas.startPoint, canvas.x_size, canvas.y_size, canvas.label};

    // Creating x and y axis.
    ax.x.set_color(Color::red);
    ax.y.set_color(Color::red);
    win.attach(ax.x);
    win.attach(ax.y);

    Mark o {Point{300,300}, 'o'}; // Making sure they meet at 300,300
    win.attach(o);

    win.attach(myf.one);
    win.attach(myf.slope);
    win.attach(myf.square);
    win.attach(myf.sloping_cos);

    win.wait_for_button();
}