#include "person.h"

std::string Person::type () {return "Person";}
std::string Person::get_name() const {return name;}
int Person::get_id() const {return id;}
bool Person::get_active () const {return active;}
void Person::set_active (bool b) { active = b;}
