#include "../../gui/Simple_window.h"
#include "../../gui/Graph.h"
using namespace Graph_lib;

// g++ oly.cpp ../../gui/Graph.cpp ../../gui/Window.cpp ../../gui/GUI.cpp ../../gui/Simple_window.cpp  -o ../../builds/oly `fltk-config --ldflags --use-images`
int main(){
        const int window_width = 600;
        const int window_height = 400;
        Simple_window win {Point{100,100}, window_width, window_height, "Olimpic Circles"};

        // Olimpic circles
        Vector_ref<Circle> circ;
        int radius = 50;
        int x_coord = 200;
        int y_coord = 200;
        for(int i = 0; i < 5; i++) {
              circ.push_back(new Circle(Point{x_coord, y_coord}, radius));
              circ[i].set_color(i);
              win.attach(circ[i]);
              x_coord += radius; // Because we want the circles to touch each other.
        }
        win.wait_for_button();
}