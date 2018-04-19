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


 double Item::get_wholesale_cost() const {return wholesale_cost;}
 double Item::get_retail_price(){return retail_price;}
 std::string Item::get_name(){return name;}
 std::string Item::get_description(){return description;}
 int Item::get_stock_remaining(){return stock_remaining;}
