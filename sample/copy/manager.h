#ifndef __MANAGER_H
#define __MANAGER_H 

#include <iostream>
#include <string>
#include "topping.h"
#include "container.h"
#include "scoop.h"
#include "items.h"

class Manager {
  private:
    std::string name;
    int employee_id;
    double hour_salary;
    Items& items;
  public:
   Manager(std::string na,int id,double salary, Items& ite):
    name {na},
    employee_id {id},
    hour_salary {salary},
    items{ite} {}

   void create_scoop();
   //void create_container();
   //void create_topping();
};
#endif
