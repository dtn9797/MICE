#include "owner.h"

Owner::Owner(std::istream& ist){
   std::getline (ist, name);
   ist >> id >> active; 
}

std::string Owner::type () {return "Owner";}
void Owner::save(std::ostream& ost){
  ost << type() << std::endl << name << std::endl
      << id << ' ' << active << ' ';
}
