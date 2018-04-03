#ifndef __TOPPING_H
#define __TOPPING_H

#include <iostream>
#include <string>
class Topping {
  private:
   std::string name;
   std::string description;
   double wholesale_cost;
   double retail_price;
   int stock_remaining;
   std::string topping_type;
   //Gtk::Image pic
  public:
   Topping(std::string na,std::string de,double wh,double re,int st,std::string type): 
   name{na}, 
   description{de}, 
   wholesale_cost{wh}, 
   retail_price{re}, 
   stock_remaining{st}, 
   topping_type{type}{};
};

#endif
