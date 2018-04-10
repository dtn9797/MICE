#include "test_serving.h"
#include "serving.h"
#include <iostream>
#include <vector>


bool test_serving () {
  std::string expected = "";
  bool passed = true; // Optimist!

  //
  // Test constructor
  //

    Container x_container("Container","This is a container",1,2,3);
    std::vector<Scoop> x_scoops={Scoop("Scoop","This is the first scoop",1,2),Scoop("Scoop","This is the second scoop",1,2)};
    std::vector<Topping> x_toppings={Topping("Toppings","These are scoops",1,2,1)};
    double x_wholesale_cost = x_container.get_wholesale_cost()+x_scoops[0].get_wholesale_cost()+x_scoops[1].get_wholesale_cost()+x_toppings[0].get_wholesale_cost();
    double x_retail_price = x_container.get_retail_price()+x_scoops[0].get_retail_price()+x_scoops[1].get_retail_price()+x_toppings[0].get_retail_price();

    Serving serving{x_container,x_scoops,x_toppings};

  if (serving.get_container().get_description() != x_container.get_description() ||
      serving.get_scoop(0).get_description() != x_scoops[0].get_description() ||
      serving.get_topping(0).get_description() != x_toppings[0].get_description() ||
      serving.get_wholesale_cost() != 4 ||
      serving.get_retail_price() !=  8) {
    std::cerr << "#### Serving constructor fail" << std::endl;
   
    std::cerr << "Expected: " << x_container.get_description()<< ','
                              << x_scoops[0].get_description()  << ','
                              << x_toppings[0].get_description() << ','
                              << '4' << ','
                              << '8' << ',' << std::endl;
    std::cerr << "Actual:   " << serving.get_container().get_description() << ','
                              << serving.get_scoop(0).get_description() << ','
                              << serving.get_topping(0).get_description()<< ','
                              << serving.get_wholesale_cost() << ','
                              << serving.get_retail_price() << std::endl;
   
    passed = false;
  }

  //
  //Check for out put
  //
  std::cout << "#####Check for cout from serving"<< std::endl
  << serving.to_string_serving() << std::endl;
  
  //
  // Report results
  //

  return passed;
} 
