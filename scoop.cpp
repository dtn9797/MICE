#include "scoop.h"

std::string Scoop::to_string () {
  std::string result = "name:" + name
     + ",description:" + description
     + ",wholesale_cost:" + std::to_string(wholesale_cost)
     + ",retail_price:" + std::to_string(retail_price)
     + ",stock_remaining:" + std::to_string(stock_remaining)
     +  "\n" ;
  return result;
}

std::string Scoop::type () {return "Scoop";}
