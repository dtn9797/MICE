#include "test_container.h"
#include "container.h"
#include <iostream>
#include <fstream>

bool test_container() {
  std::string expected = "";
  bool passed = true; // Optimist!

  //
  // Test constructor
  //

  std::string x_name = "Fudge Ripple";
  std::string x_description = "Chocolatey goodness in vanilla swirl";
  double x_cost = 0.75;
  double x_price = 1.50;
  int x_scoop_limit=10;

  Container container{x_name, x_description, x_cost, x_price,x_scoop_limit};

  if (container.get_name() != x_name ||
      container.get_description() != x_description ||
      container.get_wholesale_cost() != x_cost ||
      container.get_retail_price() != x_price ||
      container.type() != "Container" ||
      container.get_stock_remaining() != 0 ||
      container.get_scoop_limit() != x_scoop_limit) {
    std::cerr << "#### container constructor fail" << std::endl;
    std::cerr << "Expected: " << x_name << ','
                              << x_description << ','
                              << x_cost << ','
                              << x_price << ','
                              << "Container" << ','
                              << '0' << ','
			      <<x_scoop_limit<< std::endl;
    std::cerr << "Actual:   " << container.get_name() << ','
                              << container.get_description() << ','
                              << container.get_wholesale_cost() << ','
                              << container.get_retail_price() << ','
                              << container.type() << ','
                              << container.get_stock_remaining() << ','
                              <<container.get_scoop_limit()<< std::endl;
    passed = false;
  }

  //
  // Read files
  //
  std::ofstream ofs ("test_container.cpt",std::ifstream::out);
  container.save(ofs);
  ofs.close();
  std::ifstream ifs ("test_container.cpt",std::ifstream::in);
  std::string type ;
  if (std::getline (ifs, type));
  std::cout << type << std::endl;
  Container container0("D","D",1,1,1);
  if (type == "Container") {container0 = Container(ifs);};


  if (container0.get_name() != x_name ||
      container0.get_description() != x_description ||
      container0.get_wholesale_cost() != x_cost ||
      container0.get_retail_price() != x_price ||
      container0.type() != "Container" ||
      container0.get_stock_remaining() != 0 ||
      container0.get_scoop_limit() != x_scoop_limit) {
    std::cerr << "#### container constructor fail" << std::endl;
    std::cerr << "Expected: " << x_name << ','
                              << x_description << ','
                              << x_cost << ','
                              << x_price << ','
                              << "Container" << ','
                              << '0' << ','
			      <<x_scoop_limit<< std::endl;
    std::cerr << "Actual:   " << container0.get_name() << ','
                              << container0.get_description() << ','
                              << container0.get_wholesale_cost() << ','
                              << container0.get_retail_price() << ','
                              << container0.type() << ','
                              << container0.get_stock_remaining() << ','
                              <<container0.get_scoop_limit()<< std::endl;
    passed = false;
  }
  return passed;
}
