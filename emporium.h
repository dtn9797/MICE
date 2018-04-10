#ifndef EMPORIUM_H
#define EMPORIUM_H

#include <iostream>
#include <string>
#include <vector>
#include "scoop.h"
#include "container.h"
#include "topping.h"
#include "item.h"

class Emporium {
  private:
    std::vector<Item*> items;
   
  public:
    std::vector<Item*> classify_type(std::string type);
    void add_scoop(Scoop* scoop);
    void add_top(Topping* top);
    void add_container(Container* con);

    std::string item_to_string(int index);
    std::string scoop_to_string(int index);
    std::string container_to_string(int index);
    std::string topping_to_string(int index);

    int number_of_items();
    int number_of_scoops();
    int number_of_containers();
    int number_of_toppings();

    void auto_add();
};


#endif
