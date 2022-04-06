#include "../../gui/Simple_window.h"
#include "../../gui/Graph.h"

// g++ ch12drill.cpp ../../gui/Graph.cpp ../../gui/Window.cpp ../../gui/GUI.cpp ../../gui/Simple_window.cpp  -o ../../builds/ch12 `fltk-config --ldflags --use-images`
using namespace Graph_lib;

int main() {
        // Canvas variables
        const int window_width = 600;
        const int window_height = 400;
        // Axis variables
        const int scale = 10, xlen = window_width-40, ylen = window_height-40;
        const Point origo {window_width/2, window_height/2};
        // Square variables
        int rmin = -11, rmax = 11;
        int n_points = 300;

        try {
        // Create a Blank window.
        Simple_window win {Point{100,100}, window_width, window_height, "My window"};

        // Create an Image.
        Image im {Point{10,10}, "dino.jpg"};
        win.attach(im);
        win.set_label("Showing an image.");
        win.wait_for_button();

        // Create an axis for x and y.
        Axis x {Axis::x, Point{20, origo.y}, xlen, xlen/scale, "x axis"};
        Axis y {Axis::y, Point{origo.x, ylen+20}, ylen, xlen/scale, "y axis"};
        x.set_color(Color::dark_red);
        y.set_color(Color::dark_red);

        win.attach(x);
        win.attach(y);
        win.set_label("An axis.");
        win.wait_for_button();
        // Create an f(x) = x^2 / 5; function.
        Function sq ([] (double x) {return x*x / 5;}, rmin, rmax, origo, n_points, scale, scale);
        win.attach(sq);
        win.set_label("Functions.");
        win.wait_for_button();

        // Create an f(x) = cos x; function.
        Function cos_x ([] (double x) {return cos(x);}, rmin, rmax, origo, n_points, scale, scale);
        cos_x.set_color(Color::blue);
        win.attach(cos_x);
        win.wait_for_button();

        // Create a Rectangle
        Rectangle rect {Point{origo.x+50, origo.y+50}, 100, 100};
        rect.set_fill_color(Color::dark_yellow);
        win.attach(rect);
        win.set_label("A rectangle.");
        win.wait_for_button();

        // Create a Polygon
        Polygon poly;
        poly.add(Point{100, 200});
        poly.add(Point{250, 255});
        poly.add(Point{200, 300});
        poly.set_color(Color::dark_green);
        poly.set_fill_color(Color::green);
        poly.set_style(Line_style::dash);
        win.set_label("A polygon.");
        win.attach(poly);
        win.wait_for_button();

        // Create a circle
        Circle circle {Point{origo.x, origo.y}, 100};
        circle.set_color(Color::dark_magenta);
        circle.set_style(Line_style::dash);
        win.attach(circle);
        win.set_label("A Circle.");
        win.wait_for_button();

        // Create a Text
        Text text {Point{170,350}, "~I like c++ :)"};
        win.attach(text);
        win.set_label("Ch12drill by. qantanas");
        win.wait_for_button();

        } catch (exception& e) {
                cerr << "Error: " << e.what() << endl;
        }
}
