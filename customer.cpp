#include "customer.h"


Customer::Customer(std::istream& ist){
   std::getline (ist, name);
   std::getline (ist, phone_num);
   ist >> id >> active; 
}

std::string Customer::type() {return "Customer";}

std::string Customer::get_phone_num() const {return phone_num;}


    void Customer ::save(std::ostream& ost){
       ost << type() << std::endl 
           << name << std::endl 
           << phone_num << std::endl
           << id << ' ' << active << ' ';
    }

