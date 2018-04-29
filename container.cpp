#include "container.h"

Container::Container(std::istream& ist){
   std::getline (ist, name);
   std::getline (ist, description);
   ist >> wholesale_cost;ist.ignore();
   ist >> retail_price;ist.ignore();
   ist >> scoop_limit; ist.ignore();
}

std::string Container::to_string (){
  std::string result = "name:" + name
     + ",description:" + description
     + ",wholesale_cost:" + std::to_string(wholesale_cost)
     + ",retail_price:" + std::to_string(retail_price)
     + ",stock_remaining:" + std::to_string(stock_remaining)
     + ",scoop_limit:" + std::to_string(scoop_limit)
     +  "\n" ;
  return result;
}

std::string Container::type () {return "Container";}
int Container::get_scoop_limit() {return scoop_limit;}

void Container::save (std::ostream& ost){
      ost << "#" << std::endl << type() << std::endl
      << name << std::endl << description << std::endl 
      << wholesale_cost << ' ' << retail_price << ' ' 
      << scoop_limit << ' ';
 } 
