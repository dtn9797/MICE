#ifndef CASH_REGISTER_H
#define CASH_REGISTER_H

#include "order.h"
#include <iostream>
#include "server.h"
#include "item.h"
#include <vector>
#include <string>

class Cash_register {
  public:
    Cash_register(double am): amount {am} {};
    Cash_register& operator+=(const Order& order);
    Cash_register& operator-=(const Item& item);
   
    //OPERATOR OVERLOADING
    Cash_register& operator-=(const Server& server);

  
    double get_amount();
    
  private:
    double amount=1000;
};

#endif
