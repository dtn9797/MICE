#include "line.h"
#include "turtle.h"
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;

void Turtle_graphics::penUp() {pen_is_down = false;}
void Turtle_graphics::penDown() {pen_is_down = true;}
void Turtle_graphics::turn(double degrees) {angle += degrees * d2r;}
void Turtle_graphics::forward(double distance) {
  double x2 = x + distance*cos(angle);
  double y2 = y + distance*sin(angle);
  if (pen_is_down) lines.push_back(Line(x, y, x2, y2));
  x = x2;
  y = y2;
}
vector<Line> Turtle_graphics::get_lines() {return lines;}

