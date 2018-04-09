#include "test_scoop.h"
#include "scoop.h"
#include <iostream>

bool test_scoop() {
  std::string expected = "";
  bool passed = true; // Optimist!

  //
  // Test constructor
  //

  std::string x_name = "Fudge Ripple";
  std::string x_description = "Chocolatey goodness in vanilla swirl";
  double x_cost = 0.75;
  double x_price = 1.50;

  Scoop scoop{x_name, x_description, x_cost, x_price};

  if (scoop.get_name() != x_name ||
      scoop.get_description() != x_description ||
      scoop.get_wholesale_cost() != x_cost ||
      scoop.get_retail_price() != x_price ||
      scoop.type() != "Scoop" ||
      scoop.get_stock_remaining() != 0) {
    std::cerr << "#### Scoop constructor fail" << std::endl;
    std::cerr << "Expected: " << x_name << ','
                              << x_description << ','
                              << x_cost << ','
                              << x_price << ','
                              << "Scoop" << ','
                              << '0' << std::endl;
    std::cerr << "Actual:   " << scoop.get_name() << ','
                              << scoop.get_description() << ','
                              << scoop.get_wholesale_cost() << ','
                              << scoop.get_retail_price() << ','
                              << scoop.type() << ','
                              << scoop.get_stock_remaining() << std::endl;
    passed = false;
  }

  //
  // Report results
  //

  return passed;
}
