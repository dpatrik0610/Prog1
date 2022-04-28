#include "../../gui/GUI.h"

using namespace Graph_lib;

struct Lines_window : Graph_lib::Window {
	Lines_window(Point xy, int w, int h, const string& title );

private: // Private because its a window and we are communicating through callback functions.
    Open_polyline lines;

    Button next_button;
    Button quit_button;
    In_box next_x;
    In_box next_y;
    Out_box xy_out;

	// New elements: Colour and style
    Menu colour_menu;
    Button colmenu_button;
    Menu style_menu;
    Button stymenu_button;

	// Callback functions, when the buttons are clicked: 
    void change(Color c) { lines.set_color(c); }
	void change_style(Line_style s) { lines.set_style(s); }

	// When the container of colours / styles are pressed:
	void colmenu_pressed() { colmenu_button.hide(); colour_menu.show(); }
	void stymenu_pressed() { stymenu_button.hide(); style_menu.show(); }

	// Actions when any colour / style is chosen:
	void hide_colmenu() { colour_menu.hide(); colmenu_button.show(); }
	void hide_stymenu() { style_menu.hide(); stymenu_button.show(); }

	void red_pressed() { change(Color::red); hide_colmenu(); }
	void blue_pressed() { change(Color::blue); hide_colmenu(); }
	void black_pressed() { change(Color::black); hide_colmenu(); }

	void dot_pressed() { change_style(Line_style::dot); hide_stymenu(); }
	void dash_pressed() { change_style(Line_style::dash); hide_stymenu(); }
	void solid_pressed() { change_style(Line_style::solid); hide_stymenu(); }


	void next();
	void quit();

	static void cb_red(Address, Address);
    static void cb_blue(Address, Address);
    static void cb_black(Address, Address);
    static void cb_colmenu(Address, Address);

    static void sb_solid(Address, Address);
    static void sb_dash(Address, Address);
    static void sb_dot(Address, Address);
    static void sb_stymenu(Address, Address);

    static void cb_next(Address, Address);
    static void cb_quit(Address, Address);
};