#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <string>

class Person {
  public:
   Person (std::string na, int i):name{na},id{i} {}
   Person () : Person ("Unknown", 0) {} 
   virtual std::string type ();
   virtual void save(std::ostream& ost);
   std::string get_name() const;
   int get_id() const;
   bool get_active() const; 
   void set_active(bool b);
   bool operator== (const Person& rhs);
  protected:
   std::string name;
   int id;
   bool active = true;
};


#endif
