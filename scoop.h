#ifndef __SCOOP_H
#define __SCOOP_H 

#include <iostream>
#include <string>
#include <vector>
class Scoop {
  private:
   std::string name;
   std::string description;
   double wholesale_cost;
   double retail_price;
   int stock_remaining;
   std::string ice_cream_favors;
   //Gtk::Image pic
  public:
   Scoop(std::string na,std::string de,double wh,double re,int st,std::string ic): 
   name{na}, 
   description{de}, 
   wholesale_cost{wh}, 
   retail_price{re}, 
   stock_remaining{st}, 
   ice_cream_favors{ic}{};
};

#endif
