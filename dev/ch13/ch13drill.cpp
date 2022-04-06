/*
g++ ch13drill.cpp ../gui/Graph.cpp ../gui/Window.cpp ../gui/GUI.cpp ../gui/Simple_window.cpp  -o ../builds/ch13 `fltk-config --ldflags --use-images`
*/
#include "../gui/Simple_window.h"
#include "../gui/Graph.h"

class Grid {
public: // We have to acces the cell's width and height later as well as the whole grid (to attach)
    int cellWidth, cellHeight; // Width and Height of each cell.
    int scale;  // Whole scale of the grid.
    Lines grid;

    Grid(int _cellWidth, int _cellHeight, int _rate) { // Set local variable values to given parameters.
        cellWidth = _cellWidth;
        cellHeight = _cellHeight;
        if (cellWidth == cellHeight)
        {
            scale = _rate * cellWidth; // It doesn't matter if its times cellWidth or cellHeight, because they are equal.
        }
        else error("Not equal sides.");
        int gridWidth = cellWidth * _rate;
        int gridHeight = cellHeight * _rate;

        createGrid(cellWidth, cellHeight, gridWidth, gridHeight, scale);
    }
private:
    void createGrid( int cellWidth, int cellHeight, int grid_width, int grid_height, int scale){
        for ( int x = cellWidth; x <= scale; x += cellWidth)
            grid.add(Point{x,0},Point{x,grid_height});
        for ( int y = cellHeight; y <= scale; y += cellHeight)
            grid.add(Point{0,y},Point{grid_width,y});
    }
};

int main()
{
    const int window_width = 800, window_height = 1000;
    Simple_window win {Point{100,100},window_width,window_height,"Simple Window."};

    // Creating an 8 by 8 rate Grid of 100x100 squares.
    Grid myGrid(100, 100, 8);

    // Rectangle position
    int rect_xpos = 100;
    int rect_ypos = 100;

    // Basically, Vector_ref simulates a vector of references. (Book page: 811)
    Vector_ref<Rectangle> rectangles;
    for (int i = 0; i < 8; ++i) {
        //Adding a rectangle to the vector at point 100, 200... with the size of each grid ww, hh.
        rectangles.push_back(new Rectangle{Point{i * rect_xpos, i * rect_ypos}, myGrid.cellWidth, myGrid.cellHeight});
        rectangles[rectangles.size() - 1].set_fill_color(Color::red);
        win.attach(rectangles[rectangles.size() - 1]);
    }
    // putting on 3 images: 
    Image im1 {Point{200, 0}, "smile.jpg"};
    Image im2 {Point{400,200}, "smile.jpg"};
    Image im3 {Point{600,400}, "smile.jpg"};

    win.attach(myGrid.grid);
    win.attach(im1);
    win.attach(im2);
    win.attach(im3);
    win.wait_for_button();

    // Creating a movable Image:
    // Since its an 8 by 8 grid, I set the position of each image as the for loop increases * 100 (grid's width and height)
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            Image movingIm{Point{j * myGrid.cellWidth, i * myGrid.cellHeight}, "smile2.jpg"};
            win.attach(movingIm);
            win.wait_for_button();
        }
    }

    win.wait_for_button();
}