#include <iostream>
#include <fstream>
#include "line.h"
int main() {
  
  //std::ofstream ofs ("test.cpt",std::ifstream::out);
  //container.save(ofs);
  std::ifstream ifs ("untitled.ctp",std::ifstream::in);
  Line* line = new Line(ifs);
  std::cout << "x1:"  << line -> x1() << std::endl;
  return 0 ;
}
