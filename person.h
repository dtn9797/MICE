#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <string>

class Person {
  public:
   Person (std::string na, int i):name{na},id{i} {}
   virtual std::string type ();
   std::string get_name();
   int get_id();
  protected:
   std::string name;
   int id;
};


#endif
