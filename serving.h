#ifndef SERVING_H
#define SERVING_H

#include <iostream>
#include "topping.h"
#include "scoop.h"
#include "container.h"
#include <vector>

class Serving {
  private:
    Container container;
    std::vector<Scoop> scoops;
    std::vector<Topping> toppings;
    double wholesale_cost=0;
    double retail_price=0;
  public:
    Serving(Container con,std::vector<Scoop> scos,std::vector<Topping> tops) ;

    Container get_container();
    Scoop get_scoop(int index);
    Topping get_topping(int index);
    std::vector<Scoop> get_scoops();
    std::vector<Topping> get_toppings();
    double get_retail_price();
    double get_wholesale_cost();
    int get_number_scoops();
    int get_number_toppings();

    void add_scoop(Scoop sco);
    void add_top(Topping top);

    void remove_scoop(int index);
    void remove_top(int index);
    void replace_container(Container con);

    std::string to_string_serving();
};

#endif
