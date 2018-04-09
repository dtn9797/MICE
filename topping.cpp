#include "topping.h"
#include <stdexcept>

std::string Topping::type() {return "Topping";}

std::string Topping::to_string () {
  std::string result = "name:" + name
     + ",amount:"+ to_string_amount()
     + ",description:" + description
     + ",wholesale_cost:" + std::to_string(wholesale_cost)
     + ",retail_price:" + std::to_string(retail_price)
     + ",stock_remaining:" + std::to_string(stock_remaining)
     +  "\n" ;
  return result;
}

int Topping::get_amount() {return _amount;}

void Topping::_set_amount(int amount) {
    if (0 < amount && amount < 5) _amount =  amount;
    else throw std::runtime_error("Invalid topping amount");
}

std::string Topping::to_string_amount () {
  switch (_amount){
   case (LIGHT_AMOUNT) : return "Light Amount";
   case (NORMAL_AMOUNT) : return "Normal Amount";
   case (EXTRA_AMOUNT) : return "Extra Amount";
   case (DRENCHED_AMOUNT) : return "Drenched Amount";
   default : return "Unknown";
  }

}
