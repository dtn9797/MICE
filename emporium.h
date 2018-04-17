#ifndef EMPORIUM_H
#define EMPORIUM_H

#include <iostream>
#include <string>
#include <vector>
#include "scoop.h"
#include "container.h"
#include "topping.h"
#include "item.h"
#include "person.h"
#include "server.h"
#include "customer.h"
#include "order.h"
#include "owner.h"
#include "manager.h"

class Emporium {
  private:
    std::vector<Item*> items;
    std::vector<Person*> persons;
    std::vector<Order*>  orders;
   
  public:
    void add_scoop(Scoop* scoop);
    void add_top(Topping* top);
    void add_container(Container* con);
    void add_order(Order* ord);

    void add_owner (Owner* owner);
    void add_manager (Manager* manager);
    void add_server (Server* server);
    void add_customer (Customer* customer);

    std::string item_to_string(int index);
    std::string scoop_to_string(int index);
    std::string container_to_string(int index);
    std::string topping_to_string(int index);

    std::vector<Item*> get_items ();
    std::vector<Person*> get_persons ();
    std::vector<Order*> get_orders ();

    std::vector<Person*> get_active_persons () ;
    void set_active_person( int index, bool active);

    std::vector<std::string> order_to_strings(int index);    

    int number_of_items();
    int number_of_scoops();
    int number_of_containers();
    int number_of_toppings();
    int number_of_orders();

    //TEMPLATE
    template <class T>
    T classify_type(T things, std::string type) {
	T results={};	
	for (int i=0 ; i< things.size(); i++) {
  	  if (things[i]->type() == type)
	    results.push_back (things[i]);
	}
	return results;
    }

    

    void auto_add();
};


#endif
