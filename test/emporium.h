#ifndef EMPORIUM_H
#define EMPORIUM_H

#include <iostream>
#include <string>
#include <vector>
#include "order.h"


class Emporium {
  private:
    std::vector<Order*>  orders;
  public:
    std::vector<Order*> get_orders ();
    void add_order (Order* order);   
    std::vector<std::string> order_to_strings(int index);
    std::string servings_to_string (int order_index);    
    int number_of_orders();
    void auto_add();
};


#endif
