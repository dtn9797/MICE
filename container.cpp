#include "container.h"

std::string Container::to_string (){
  std::string result = "name:" + name
     + ",description:" + description
     + ",wholesale_cost:" //+ wholesale_cost
     + ",retail_price:" //+ retail_price
     + ",stock_remaining:"// + stock_remaining
     + ",scoop_limit:" //+ scoop_limit
     +  "\n" ;

  return result;
}
