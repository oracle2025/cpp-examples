#include "lib.h"
#include <FL/Fl.H>
#include <FL/fl_draw.H>

const char* string_from_lib()
{
	return "Hello From Lib";
}

class DrawX : public Fl_Widget {
public:
    DrawX(int X, int Y, int W, int H, const char*L=0) : Fl_Widget(X,Y,W,H,L) {
    }
    void draw() {
        // DRAW BLACK 'X'
        fl_color(FL_BLACK);
        int x1 = x(),       y1 = y();
        int x2 = x()+w()-1, y2 = y()+h()-1;
        fl_line(x1, y1, x2, y2);
        fl_line(x1, y2, x2, y1);
    }
};

void * get_widget() {
	return new DrawX(0,0, 100,100);
}

