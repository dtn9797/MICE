#include <iostream>
#include "test_cash_register.h"
#include "cash_register.h"
#include "server.h"
#include "scoop.h"
#include "person.h"
#include "order.h"

bool test_cash_register() {
  std::string expected = "";
  bool passed = true; // Optimist!

  //
  // Test constructor
  //
  Cash_register c(2000);
  if (c.get_amount()!=2000){
    std::cerr << "Cash register Constructor failed !" << std::endl;
    passed = false;
  }

  //
  // Test operator over loading
  //

  Server server("Duy",1,100);
  c-=server;
  if (c.get_amount()!=1900){
    std::cerr << "Cash register -= overflow failed !" << std::endl;
    passed = false;
  }

  Item item ("D","D",1,1);
  c-=item;
  if (c.get_amount()!=1899){
    std::cerr << "Cash register -= overloading for item failed !" << std::endl;
    passed = false;
  }

  Scoop scoop ("D","D",1,1);
  c-=scoop;
  if (c.get_amount()!=1898){
    std::cerr << "Cash register -= overloading for item failed !" << std::endl;
    passed = false;
  }

  std::vector<Scoop> scoops = {Scoop ("Vanilla","General",1,1),Scoop ("Cookies", "Sweet",1,1)};
  std::vector<Topping> tops = {Topping("Whipped Cream","General",1,1,1), Topping("Chocolate Sauce", "Sweet",1,1,1) };
  Serving serving0 ( Container ("Cup","General",1,1,1), scoops, tops );
  Order order0(1,server);
  order0.add_serving(serving0); 
  c+=order0;
  if (c.get_amount()!=1903){
    std::cerr << "Cash register += overloading for item failed !" << std::endl;
    passed = false;
  }
     

  return passed;


}
