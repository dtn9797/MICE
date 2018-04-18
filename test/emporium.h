#ifndef EMPORIUM_H
#define EMPORIUM_H

#include <iostream>
#include <string>
#include <vector>
#include "order.h"


class Emporium {
  private:
    std::vector<Order*>  orders;
  public:

    std::vector<Order*> get_orders ();

    void add_order (Order* order);   
 
    std::vector<std::string> order_to_strings(int index);
    std::string servings_to_string (int order_index);    


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
