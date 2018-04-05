#ifndef __SCOOP_H
#define __SCOOP_H 

#include <iostream>
#include <string>
#include "items.h"

class Scoop:public Items {
  public:
   Scoop(std::string na,std::string de,double wh,double re,int st): 
   Items(na,de,wh,re,st){};
   std::string to_string();
};

#endif
