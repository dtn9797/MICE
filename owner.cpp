#include "owner.h"

Owner::Owner(std::istream& ist){
   std::getline (ist, name);
   ist >> id; ist.ignore(); 
   ist >> active; ist.ignore();
}

std::string Owner::type () {return "Owner";}
void Owner::save(std::ostream& ost){
  ost << "#" << std::endl << type() << std::endl;
  ost << name << std::endl
      << id << ' ' << active << ' ';
}
