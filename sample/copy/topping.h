#ifndef __TOPPING_H
#define __TOPPING_H

#include <iostream>
#include <string>
#include "items.h"

class Topping:public Items{

  public:
   Topping(std::string na,std::string de,double wh,double re,int st):
     Items(na,de,wh,re,st){};
   std::string to_string();
};

#endif
