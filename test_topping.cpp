#include "test_topping.h"
#include "topping.h"
#include <iostream>

bool test_topping() {
  std::string expected = "";
  bool passed = true; // Optimist!

  //
  // Test constructor
  //

  std::string x_name = "Maraschino Cherry";
  std::string x_description = "A sweet, plump cherry preserved in maraschino syrup";
  double x_cost = 0.10;
  double x_price = 0.50;
  int x_amount = Topping::EXTRA_AMOUNT;

  Topping topping{x_name, x_description, x_cost, x_price, x_amount};

  if (topping.get_name() != x_name ||
      topping.get_description() != x_description ||
      topping.get_wholesale_cost() != x_cost ||
      topping.get_retail_price() != x_price ||
      topping.type() != "Topping" ||
      topping.get_amount() != Topping::EXTRA_AMOUNT) {
    std::cerr << "#### Topping constructor fail" << std::endl;
    std::cerr << "Expected: " << x_name << ','
                              << x_description << ','
                              << x_cost << ','
                              << x_price << ','
                              << "Topping" << ','
                              << x_amount << std::endl;
    std::cerr << "Actual:   " << topping.get_name() << ','
                              << topping.get_description() << ','
                              << topping.get_wholesale_cost() << ','
                              << topping.get_retail_price() << ','
                              << topping.type() << ','
                              << topping.get_amount() << std::endl;
    passed = false;
  }

  //
  // Report results
  //

  return passed;
}
