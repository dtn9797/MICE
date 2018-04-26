#include "person.h"

std::string Person::type () {return "Person";}
std::string Person::get_name() const {return name;}
int Person::get_id() const {return id;}
bool Person::get_active () const {return active;}
void Person::set_active (bool b) { active = b;}
bool Person::operator== (const Person& rhs){
  return name == rhs.get_name() && id == rhs.get_id();
}
void Person::save(std::ostream& ost){
  ost << type() << ' '<< name << ' ' 
      << id << ' ' << active << ' ';
}
