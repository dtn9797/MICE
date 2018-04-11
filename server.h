#ifndef SERVER_H
#define SERVER_H

#include "person.h"
#include <iostream>
#include <string>
class Server : public Person {
  public:
    Server (std::string na, int id, double sal): Person(na,id), hour_salary{sal} {}
    std::string type() override;

    double get_hour_salary();
    int get_num_order_filled();
    
    void add_order_filled();
  private:
    int num_order_filled=0;
    double hour_salary;
};


#endif
