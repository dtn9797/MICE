#include "cash_register.h"

    Cash_register& Cash_register::operator+=(const Order& order){
      amount += order.get_price();
      return *this;
    }
    Cash_register& Cash_register::operator-=(const Item& item){
      amount -= item.get_wholesale_cost();
      return *this;
    }
    Cash_register& Cash_register::operator-=(const Server& server){
      amount -= server.get_hour_salary();
      return *this;
    }
 
    double Cash_register::get_amount {return amount;}


