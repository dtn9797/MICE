#ifndef ORDER_H
#define ORDER_H

#include "state.h"
#include <iostream>
#include "serving.h"
#include "customer.h"
#include "server.h"
#include <vector>
#include <string>

class Order {
  public: 
    Order (int id, Person &per): id_number{id} {
      if (per.type() == "Server"){ server= *(dynamic_cast<Server*>(&per));}
      else if (per.type() == "Customer"){customer= *(dynamic_cast<Customer*>(&per));}      
    }
    //Order (int id, Customer &cus): id_number{id}, customer{cus}{}
    //Order (int id,Server ser, std::vector<Serving> sers): id_number{id}, server{ser} ,servings{sers} {}
    //Order (int id,Customer cus, std::vector<Serving> sers): id_number{id},customer{cus}, servings{sers} {}
    //Copy Constructor

    void fill(Server &server);
    void pay();
    void cancel();

    void add_serving(Serving& serving);

    int get_id_number ();
    std::vector<Serving> get_servings();
    State get_state();
    double get_cost();
    double get_price();
    Server get_server();
    Customer get_customer();

    int number_of_servings();
    
    //std::string serving_to_string (int index);
       
    std::vector<std::string> to_strings();
  private:
    int id_number;
    std::vector<Serving> servings ={};
    State state = State :: unfilled;
    double cost=0;
    double price=0;
    Server server;
    Customer customer;

};

#endif
