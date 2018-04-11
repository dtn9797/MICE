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
     Item(na,de,wh,re){_amount = am;};
    std::string to_string() override;
    std::string type() override;
    int get_amount();
    void set_amount(int amount);
    const static int LIGHT_AMOUNT = 1;
    const static int NORMAL_AMOUNT = 2;
    const static int EXTRA_AMOUNT = 3;
    const static int DRENCHED_AMOUNT = 4;
    std::string to_string_amount ();
  private:
    int _amount;
};

#endif
