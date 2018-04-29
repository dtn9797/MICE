#include "customer.h"


Customer::Customer(std::istream& ist){
   std::string id_str ;
   getline (ist, name);
   getline (ist, phone_num);
   getline (ist, id_str);
   id = std::stoi(id_str);
}

std::string Customer::type() {return "Customer";}

std::string Customer::get_phone_num() const {return phone_num;}


    void Customer ::save(std::ostream& ost){
       ost << "#" << std::endl << "Customer" << std::endl; // header
       ost << name << std::endl 
           << phone_num << std::endl
           << id << std::endl;
    }

