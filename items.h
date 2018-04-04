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
      stock_remaining{s} {}

  protected:
    std::string name;
    std::string description;
    double wholesale_cost;
    double retail_price;
    int stock_remaining;
    //Image picture;
};

#endif
