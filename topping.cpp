#include "topping.h"
#include <stdexcept>

Topping::Topping(std::istream& ist){
   std::getline (ist, name);
   std::getline (ist, description);
   ist >> wholesale_cost; ist.ignore(); 
   ist >> retail_price; ist.ignore();
   ist >> _amount; ist.ignore();
}

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

void Topping::set_amount(int amount) {
    if (0 < amount && amount < 5) _amount =  amount;
    else throw std::runtime_error("Invalid topping amount");
}

void Topping::save (std::ostream& ost){
   ost << "#" << std::endl << type() << std::endl
       << name << std::endl << description << std::endl
       << wholesale_cost << ' ' << retail_price << ' ' 
       << _amount << ' ';
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
