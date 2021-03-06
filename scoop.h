#ifndef __SCOOP_H
#define __SCOOP_H 

#include <iostream>
#include <string>
#include "item.h"

//
//POLYMORPHISM
//

class Scoop:public Item {
  public:
   Scoop(std::string na,std::string de,double wh,double re): 
   Item(na,de,wh,re){};
   std::string to_string() override;
   std::string type () override;
};

#endif
