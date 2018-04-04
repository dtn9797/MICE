#ifndef __CONTAINER_H
#define __CONTAINER_H 

#include <iostream>
#include <string>
#include "items.h"

class Container:public Items {
  protected:
   int scoop_limit;
  public:
   Container(std::string na,std::string de,double wh,double re,int st,int li): 
     Items(na,de,wh,re,st){ scoop_limit = li;};
   std::string to_string();

};

#endif
