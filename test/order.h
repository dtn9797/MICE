#ifndef ORDER_H
#define ORDER_H

#include "state.h"
#include <iostream>
#include <vector>
#include <string>

class Order {
  public: 
    Order (int id): id_number{id} {}
    std::vector<std::string> to_strings();
  private:
    int id_number;
    State state = State :: unfilled;
    double cost=0;
    double price=0;
};

#endif
