#include "topping.h"

std::string Topping::to_string () {
  std::string result = "name:" + name
     + ",description:" + description
     + ",wholesale_cost:"// + wholesale_cost
     + ",retail_price:" //+ retail_price
     + ",stock_remaining:"// + stock_remaining
     +  "\n" ;
  return result;
}
