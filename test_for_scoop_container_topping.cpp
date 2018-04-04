#include <iostream>
#include <string>
#include "scoop.h"
#include "topping.h"
#include "container.h"

int main () {
  //test for topping class
   Topping top ("Light","It is very light",.25,.5,10); 
   std::cout << top.to_string() <<std::endl;
 
  //test for scoop class
   Scoop scoop ("D","D",2,2,2);
   std::cout << scoop.to_string()<<std::endl;

  //test for container class
   Container container("Bowls","General",.25,.5,10,5);
   std::cout << container.to_string()<<std::endl;
  
  return 0;
}
