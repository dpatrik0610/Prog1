#include <iostream>
#include <string>
#include "../../gui/Lines_window.h"

//g++ ../../gui/Graph.cpp ../../gui/Window.cpp ../../gui/GUI.cpp ../../gui/Lines_window.cpp ch16.cpp `fltk-config --ldflags --use-images` -o ../../builds/ch16

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