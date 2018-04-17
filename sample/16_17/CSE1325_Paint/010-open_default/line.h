#ifndef _LINE_H
#define _LINE_H
#include <gdkmm/rgba.h>
#include <iostream>
#include <fstream>

class Line {    // Define a line from (x1, y1) to (x2, y2)
   public:
     Line(double p_x1, double p_y1,double p_x2, double p_y2, Gdk::RGBA p_color, double p_width);
     Line(std::istream& ist);

     double x1();
     double y1();
     double x2();
     double y2();
     Gdk::RGBA color();
     double width();
     void save(std::ostream& ost);
  private:
     double _x1, _y1, _x2, _y2;
     Gdk::RGBA _color;
     double _width;
};
#endif
