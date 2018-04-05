#include "items.h"

 void Items::restock (int amount ) {stock_remaining = amount ;}
 void Items::consume (int amount ) {stock_remaining -= 1;}
 std::string Items::type() {return "Item"; }

 std::string Items::to_string(){
   std::string result = "type:"+ type() +"name:" + name
     + ",description:" + description
     + ",wholesale_cost:" + std::to_string(wholesale_cost)
     + ",retail_price:" + std::to_string(retail_price)
     + ",stock_remaining:" + std::to_string(stock_remaining)
     +  "\n" ;
  return result;
}
