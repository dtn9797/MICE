#include "cash_register.h"

    Cash_register& Cash_register::operator+=(const Order& order){
      this->amount += order.get_price();
      return *this;
    }

    Cash_register& Cash_register::operator-=(const Item& item){
      this->amount -= item.get_wholesale_cost();
      if (amount < 0) throw std::runtime_error ("There is not enough money to buy "+item.get_name()); 
      return *this;
    }

    Cash_register& Cash_register::operator-=(const Server& server){
      amount -= server.get_hour_salary();
      if (amount < 0) throw std::runtime_error ("There is not enough money to pay for "+server.get_name()); 
      return *this;
    }


    double Cash_register::get_amount() {return amount;}


