#ifndef __TOPPING_H
#define __TOPPING_H

#include <iostream>
#include <string>
#include "item.h"


//
//POLYMORPHISM
//


class Topping:public Item{

  public:
    Topping(std::string na,std::string de,double wh,double re, int am):
     Item(na,de,wh,re){_amount = am;}
    Topping(std::string na,std::string de,double wh,double re):
     Item(na,de,wh,re){}
    Topping(std::string na,std::string de,double wh,double re, int am,std::string i):
     Item(na,de,wh,re,i){_amount = am;}
    Topping(std::istream &ist);
    std::string to_string() override;
    std::string type() override;
    int get_amount();
    void set_amount(int amount);
    const static int LIGHT_AMOUNT = 1;
    const static int NORMAL_AMOUNT = 2;
    const static int EXTRA_AMOUNT = 3;
    const static int DRENCHED_AMOUNT = 4;
    std::string to_string_amount ();
    void save(std::ostream& ost) override;
  private:
    int _amount;
};

#endif
