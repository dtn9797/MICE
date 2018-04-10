#ifndef ORDER_H
#define ORDER_H

#include "state.h"
#include <iostream>
#include "serving.h"
#include <vector>

class Order {
  public: 
    Order (int id,vector<Serving> sers);
    fill()
  private:
    int id;
    vector<Serving> servings;
    State state;
    double cost;
    double price;
    //Server server;
    //Customer customer;

};

#endif
