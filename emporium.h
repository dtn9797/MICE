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
#include "cash_register.h"

class Emporium {
  private:
    std::vector<Item*> items;
    std::vector<Person*> persons;
    std::vector<Order*>  orders;
    Cash_register* cash_register_ptr = new Cash_register(1000);
    bool dirty = false;
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
    std::vector<Order*> get_unfilled_orders ();
    std::vector<Order*> get_unfilled_orders_for_customer (Person* person_ptr);
    std::vector<Order*> get_filled_orders ();
    std::vector<Order*> get_canceled_orders ();

    std::vector<Person*> get_active_persons () ;
    void set_active_person( int index, bool active);

    std::string servings_to_string (int order_index);    

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

    
    void restock_item(int index, int amount);
    void fill_order (int index, Server* server_ptr);
    void cancel_order(int index, Person* person_ptr);
    void pay_order(int index, Person* person_ptr);

    void auto_add();
    //files
    void save(std::ostream& ost);
    void load(std::istream& ist);
    void new_item_person(std::istream& ist, std::string type);
    void new_order(std::istream& ist);
    void clear ();

};


#endif
