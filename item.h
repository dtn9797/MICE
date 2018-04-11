#ifndef __ITEMS_H
#define __ITEMS_H 

#include <iostream>
#include <string>

//
//POLYMORPHISM
//

class Item {
  public:
    Item (std::string n,std::string d, double c, double p):
      name{n},
      description{d},
      wholesale_cost{c},
      retail_price{p},
      stock_remaining{0} {}
     void restock (int amount =25);
     void consume (int amount =1);
     virtual std::string type();
     virtual std::string to_string();

     std::string get_name();
     std::string get_description();
     double get_wholesale_cost();
     double get_retail_price();
     int get_stock_remaining();
  protected:
    std::string name;
    std::string description;
    double wholesale_cost=0;
    double retail_price=0;
    int stock_remaining=0;
    //Image picture;
};

#endif
