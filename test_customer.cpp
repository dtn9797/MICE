#include "test_customer.h"
#include <iostream>
#include "customer.h"
#include <fstream>
bool test_customer () {
  std::string expected = "";
  bool passed = true; // Optimist!

  //
  // Test constructor
  //

  std::string x_name = "Duy Nguyen";
  int x_id =12345;
  std::string x_phone_num = "9999999999";

  Customer customer (x_name,x_id,x_phone_num);
//Test construction
  if (customer.get_name() != x_name ||
      customer.get_id() != x_id ||
      customer.type() != "Customer"||
      customer.get_phone_num () != "9999999999") {
    std::cerr << "#### Customer constructor fail" << std::endl;
    std::cerr << "Expected: " << x_name << ',' 
                              << x_id << ','
                              << "Customer" << ','
                              << x_phone_num << std::endl;
    std::cerr << "Actual:   " << customer.get_name() << ',' 
                              << customer.get_id() << ','
                              << customer.type() << ','
                              << customer.get_phone_num()<< std::endl;
    passed = false;
  }

  //
  // Read files
  //
  std::ofstream ofs ("test_customer.cpt",std::ifstream::out);
  customer.save(ofs);
  ofs.close();
  std::ifstream ifs ("test_customer.cpt",std::ifstream::in);
  std::string type ;
  if (std::getline (ifs, type));
  //std::cout << type << std::endl;
  Customer customer0("D",1,"999");
  if (type == "Customer") {customer0 = Customer(ifs);};


  if (customer0.get_name() != x_name ||
      customer0.get_id() != x_id ||
      customer0.type() != "Customer"||
      customer0.get_phone_num () != "9999999999") {
    std::cerr << "#### Customer constructor fail" << std::endl;
    std::cerr << "Expected: " << x_name << ',' 
                              << x_id << ','
                              << "Customer" << ','
                              << x_phone_num << std::endl;
    std::cerr << "Actual:   " << customer0.get_name() << ',' 
                              << customer0.get_id() << ','
                              << customer0.type() << ','
                              << customer0.get_phone_num()<< std::endl;
    passed = false;
  }


  return passed;
}
