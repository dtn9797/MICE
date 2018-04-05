#ifndef __ITEMS_H
#define __ITEMS_H 

#include <iostream>
#include <string>

class Items {
  public:
    Items (std::string n,std::string d, double c, double p, int s):
      name{n},
      description{d},
      wholesale_cost{c},
      retail_price{p},
      stock_remaining{0} {}
     void restock (int amount =25);
     void consume (int amount =1);
     virtual std::string type();
     virtual std::string to_string();

  protected:
    std::string name;
    std::string description;
    double wholesale_cost;
    double retail_price;
    int stock_remaining;
    //Image picture;
};

#endif
