#ifndef _TURTLE_H
#define _TURTLE_H

#include "line.h"
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;

class Turtle_graphics {
       const double d2r = M_PI/180.0; // Degrees to radians
       double x, y, angle; // Current turtle position
       bool pen_is_down;
       vector<Line> lines;
    public: 
       void penUp();
       void penDown();
       void turn(double degrees);
       void forward(double distance);
       vector<Line> get_lines();
};
#endif
