#include <iostream>
#include <string>
#include "../../gui/GUI.h"
#include "Lines_window.h"

//g++ ../../gui/Graph.cpp ../../gui/Window.cpp ../../gui/GUI.cpp ./Lines_window.cpp ch16.cpp `fltk-config --ldflags --use-images` -o ../../builds/ch16
// I forgot to upload the gui parts (Lines window and its header) back then. sorry.
int main(){
try{
	Lines_window win {Point{100,100},1000,1000,"lines"};
	return gui_main();
} catch(exception& e){
	cerr << "error: " << e.what() << endl;
	return 1;
} catch(...){
	cerr << "exception\n";
	return 2;
    }
}