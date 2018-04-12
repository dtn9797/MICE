#include "test_customer.h"
#include <iostream>
#include "customer.h"
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

  return passed;
}
