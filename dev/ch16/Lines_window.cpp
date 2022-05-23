#include "Lines_window.h"

Lines_window::Lines_window(Point xy, int w, int h, const string& title) 
    :Window{xy,w,h,title},
    next_button{Point{x_max()-300,0}, 150, 40, "Next point",
        [](Address, Address pw) {reference_to<Lines_window>(pw).next();}},
    quit_button{Point{x_max()-150,0}, 150, 40, "Quit",
        [](Address, Address pw) {reference_to<Lines_window>(pw).quit();}},
    next_x{Point{300,0}, 50, 40, "next x:"},
    next_y{Point{450,0}, 50, 40, "next y:"},
    xy_out{Point{100,0}, 100, 40, "current (x,y):"},

    // Basically all of these are a copy from the book (except style menu).
    // Defining our buttons. 
    colour_menu{Point{x_max()-100,60},100, 20,Menu::vertical,"colour"},
    colmenu_button{Point{x_max()-100,70}, 100, 20, "colour menu",
        [](Address, Address pw) {reference_to<Lines_window>(pw).colmenu_pressed();}},
    style_menu{Point{x_max()-100,130},100, 20,Menu::vertical,"style"},
    stymenu_button{Point{x_max()-100,140}, 100, 20, "style menu",
        [](Address, Address pw) {reference_to<Lines_window>(pw).stymenu_pressed();}}
{

    // Displaying elements:
    attach(next_button);
    attach(quit_button);
    attach(next_x);
    attach(next_y);
    attach(xy_out);
    attach(lines);
    xy_out.put("no point");

    // Attaching colours to the colour menu.
    // red is simply a sorter version with lambda funciton. Addresses: Pointers to window and widget.
    colour_menu.attach(new Button(Point(0,0),0,0,"red",[](Address, Address pw){reference_to<Lines_window>(pw).red_pressed();}));
    colour_menu.attach(new Button(Point(0,0),0,0,"blue",cb_blue));
    colour_menu.attach(new Button(Point(0,0),0,0,"black",cb_black));
    // Attaching to the screen, but hiding it, since its gonna be open when clicked.
    attach(colour_menu);
    colour_menu.hide();
    attach(colmenu_button);

    // Attaching styles to the style menu.
    style_menu.attach(new Button(Point(0,0),0,0,"solid",sb_solid));
    style_menu.attach(new Button(Point(0,0),0,0,"dashed",sb_dash));
    style_menu.attach(new Button(Point(0,0),0,0,"dotted",sb_dot));
    // Attaching to the screen, but hiding it, since its gonna be open when clicked.
    attach(style_menu);
    style_menu.hide();
    attach(stymenu_button);
    
    attach(lines);
}

void Lines_window::quit()
{
    hide();
}

void Lines_window::next()  // Getting a pair of coordinates, updates current position and redrawing the window.
{
    int x = next_x.get_int();
    int y = next_y.get_int();

    lines.add(Point{x,y});

    ostringstream ss;
    ss << '(' << x << ',' << y << ')';
    xy_out.put(ss.str());

    redraw();
}

// Buttons for colours.
void Lines_window::cb_red(Address, Address pw){ reference_to<Lines_window>(pw).red_pressed(); }

void Lines_window::cb_blue(Address, Address pw){ reference_to<Lines_window>(pw).blue_pressed(); }

void Lines_window::cb_black(Address, Address pw){ reference_to<Lines_window>(pw).black_pressed(); }

void Lines_window::cb_colmenu(Address, Address pw){ reference_to<Lines_window>(pw).colmenu_pressed(); }

// Buttons for styles.

void Lines_window::sb_solid(Address, Address pw){ reference_to<Lines_window>(pw).solid_pressed(); }

void Lines_window::sb_dash(Address, Address pw){ reference_to<Lines_window>(pw).dash_pressed(); }

void Lines_window::sb_dot(Address, Address pw){ reference_to<Lines_window>(pw).dot_pressed(); }

void Lines_window::sb_stymenu(Address, Address pw){ reference_to<Lines_window>(pw).stymenu_pressed(); }