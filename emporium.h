#ifndef EMPORIUM_H
#define EMPORIUM_H

#include <iostream>
#include <string>
#include <vector>
#include "scoop.h"
#include "container.h"
#include "topping.h"

class Emporium {
  private:
    std::vector<Scoop*> scoops;
    std::vector<Topping*> tops;
    std::vector<Container*> containers;

  public:
    void add_scoop(Scoop* scoop);
    void add_top(Topping* top);
    void add_container(Container* con);

    string scoop_to_string(int index);
    string top_to_string(int index);
    string container_to_string(int index);

    int number_of_scoop();
    int number_of_top();
    int number_of_container();
};


#endif
