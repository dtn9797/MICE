#include "line.h"
#include <gtkmm.h>

Line::Line(double p_x1, double p_y1,double p_x2, double p_y2, Gdk::RGBA p_color, double p_width) 
        : _x1{p_x1}, _y1{p_y1}, _x2{p_x2}, _y2{p_y2}, _color{p_color}, _width{p_width} { }
double Line::x1() {return _x1;}
double Line::y1() {return _y1;}
double Line::x2() {return _x2;}
double Line::y2() {return _y2;}
Gdk::RGBA Line::color() {return _color;}
double Line::width() {return _width;}
void Line::save(std::ostream& ost) {
    ost << _x1    << ' ' << _y1    << ' ' << _x2 << ' ' << _y2 << ' ' 
        << _width << ' ' << _color.to_string() << ' ';
}
