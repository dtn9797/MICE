#ifndef __CONTAINER_H
#define __CONTAINER_H 

#include <iostream>
#include <string>
#include "item.h"

//
//POLYMORPHISM
//

class Container:public Item {
  protected:
   int scoop_limit;
  public:
    Container(std::string na,std::string de,double wh,double re,int li): 
    Item(na,de,wh,re){ scoop_limit = li;}
    Container(): Container("","",0,0,0){}
    Container(std::istream& ist);

    int get_scoop_limit();
    std::string to_string() override;
    std::string type() override;
    void save(std::ostream& ost) override;

};

#endif
