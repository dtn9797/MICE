#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <string>

class Person {
  public:
   Person (std::string na, int i):name{na},id{i} {}
   Person () : Person ("Unknown", 0) {} 
   virtual std::string type ();
   std::string get_name() const;
   int get_id() const;
   bool get_active() const; 
   void set_active(bool b);
  protected:
   std::string name;
   int id;
   bool active = true;
};


#endif
