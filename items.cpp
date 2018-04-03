#include "items.h"

void Items::add_scoop (Scoop* scoop){
  scoops.push_back(scoop);
  std::cout<< scoops[0]->name << std::endl;
}
