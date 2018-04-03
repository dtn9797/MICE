#ifndef __CONTAINER_H
#define __CONTAINER_H 

#include <iostream>
#include <string>

class Container {
  private:
   std::string name;
   std::string description;
   double wholesale_cost;
   double retail_price;
   int stock_remaining;
   std::string container_type;
   int scoop_limit;
   //Gtk::Image pic
  public:
   Container(std::string na,std::string de,double wh,double re,int st,std::string type, int sc): 
   name{na}, 
   description{de}, 
   wholesale_cost{wh}, 
   retail_price{re}, 
   stock_remaining{st}, 
   container_type{type},
   scoop_limit{sc}{};
};

#endif
