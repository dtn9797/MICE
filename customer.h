#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "person.h"
#include <iostream>
#include <string>
class Customer : public Person {
  public:
    Customer (std::string na, int id, std::string ph): Person(na,id), phone_num{ph} {}
    Customer () : Customer("", 0, "00") { };
    std::string type() override;

    std::string get_phone_num() const;

  private:
    std::string phone_num;
};


#endif
