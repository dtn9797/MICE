#include "item.h"

 void Item::restock (int amount ) {stock_remaining = amount ;}
 void Item::consume (int amount ) {stock_remaining -= 1;}
 std::string Item::type() {return "Item"; }

 std::string Item::to_string(){
   std::string result = "type:"+ type() +"name:" + name
     + ",description:" + description
     + ",wholesale_cost:" + std::to_string(wholesale_cost)
     + ",retail_price:" + std::to_string(retail_price)
     + ",stock_remaining:" + std::to_string(stock_remaining)
     +  "\n" ;
  return result;
}
