#include "manager.h"

Manager::Manager(std::istream& ist){
   std::getline (ist, name);
   ist >> id >> active >> hour_salary; 
}


std::string Manager::type()  { return "Manager";}

double Manager::get_hour_salary() const {return hour_salary;}

void Manager::save(std::ostream& ost){
       ost << type() << std::endl 
           << name << std::endl 
           << id << ' ' << active << ' '
           << hour_salary << ' ';
    }
