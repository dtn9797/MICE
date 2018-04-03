#ifndef __ITEMS_H
#define __ITEMS_H 

#include <iostream>
#include "topping.h"
#include "container.h"
#include "scoop.h"
#include <vector>

class Items{
  public:
    void add_scoop(Scoop* scoop);
  private:
    std::vector<Scoop*> scoops;
    //std::vector<Topping> tops;
    //std::vector<Container> containers;
}; 

#endif
