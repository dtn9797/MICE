#ifndef MANAGER_H
#define MANAGER_H

#include "person.h"
#include <iostream>
#include <string>
class Manager : public Person {
  public:
    Manager (std::string na, int id, double salary): Person(na,id), hour_salary{salary} {}
    Manager () : Manager("", 0,0) { };
    std::string type() override;

    double get_hour_salary() const ;
  private:
    double hour_salary;

};


#endif
