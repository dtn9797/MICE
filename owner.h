#ifndef OWNER_H
#define OWNER_H

#include "person.h"
#include <iostream>
#include <string>
class Owner : public Person {
  public:
    Owner (std::string na, int id): Person(na,id) {}
    Owner () : Owner("", 0) { }
    Owner(std::istream& ist);
    std::string type() override;
    void save(std::ostream& ost) override;

};


#endif
