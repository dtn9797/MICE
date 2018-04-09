#include "test_serving.h"
#include "serving.h"
#include <iostream>
/*

bool test_serving () {
  std::string expected = "";
  bool passed = true; // Optimist!

  //
  // Test constructor
  //

    Container x_container("Container","This is a container",1,2,3);
    std::vector<Scoop> x_scoops={Scoop("Scoop","This is the first scoop",1,2),Scoop("Scoop","This is the second scoop",1,2)};
    std::vector<Topping> x_toppings={Topping("Toppings","These are scoops",1,2)};
    double x_wholesale_cost = x_container.wholesale_cost()+x_scoops[0].wholesale_cost()+x_scoops[1].wholesale_cost()+x_toppings[0].wholesale_cost();
    double x_retail_price = x_container.retail_price()+x_scoops[0].retail_price()+x_scoops[1].retail_price()+x_toppings[0].retail_price();

    Serving serving{x_container,x_scoops,x_toppings};

  if (serving.container() != x_container ||
      serving.scoops() != x_scoops ||
      serving.toppings() != x_toppings ||
      serving.wholesale_cost() != 4 ||
      serving.retail_price() !=  8) {
    std::cerr << "#### Serving constructor fail" << std::endl;
    
    std::cerr << "Expected: " << x_name << ','
                              << x_description << ','
                              << x_cost << ','
                              << x_price << ','
                              << "Container" << ','
                              << x_max_scoops << std::endl;
    std::cerr << "Actual:   " << container.name() << ','
                              << container.description() << ','
                              << container.cost() << ','
                              << container.price() << ','
                              << container.type() << ','
                              << container.max_scoops() << std::endl;
   
    passed = false;
  }

  //
  // Report results
  //

  return passed;
} 
*/
