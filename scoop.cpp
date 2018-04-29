#include "scoop.h"

Scoop::Scoop(std::istream& ist){
   std::getline (ist, name);
   std::getline (ist, description);
   ist >> wholesale_cost; ist.ignore();  
   ist >> retail_price; ist.ignore();
}

std::string Scoop::to_string () {
  std::string result = "name:" + name
     + ",description:" + description
     + ",wholesale_cost:" + std::to_string(wholesale_cost)
     + ",retail_price:" + std::to_string(retail_price)
     + ",stock_remaining:" + std::to_string(stock_remaining)
     +  "\n" ;
  return result;
}

std::string Scoop::type () {return "Scoop";}

void Scoop::save (std::ostream& ost){
   ost << "#" << std::endl << type() << std::endl
       << name << std::endl << description << std::endl
       << wholesale_cost << ' ' << retail_price << ' ';
 } 
