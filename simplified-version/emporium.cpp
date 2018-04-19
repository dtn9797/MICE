#include "emporium.h"
#include <stdlib.h>


    std::vector<Order*>  Emporium::get_orders () {return orders;}


    std::vector<std::string> Emporium::order_to_strings(int index) { return orders[index]->to_strings();}


    int Emporium::number_of_orders() {
      return orders.size();
    }

    void Emporium::add_order (Order* order) {
      orders.push_back(order);
    }

    void Emporium::auto_add() {
      Order order0(1);
      add_order(&order0);  
      std::vector<std::string> record = order_to_strings(0);
      std::cout << "This is printing from emporium.cpp class" <<std::endl 
                << "Id:" << record[0] <<"State: "<< record[1]<<"Price:"<< record[2]<< std::endl;    
    }
