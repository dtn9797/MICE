#include "test_person.h"
#include <iostream>
#include "person.h"
bool test_person () {
  std::string expected = "";
  bool passed = true; // Optimist!

  //
  // Test constructor
  //

  std::string x_name = "Duy Nguyen";
  int x_id =12345;

  Person person (x_name,x_id);
//Test construction
  if (person.get_name() != x_name ||
      person.get_id() != x_id ||
      person.type() != "Person") {
    std::cerr << "#### Item constructor fail" << std::endl;
    std::cerr << "Expected: " << x_name << ',' 
                              << x_id << ','
                              << "Person" << std::endl;
    std::cerr << "Actual:   " << person.get_name() << ',' 
                              << person.get_id() << ','
                              << person.type() << std::endl;
    passed = false;
  }

  return passed;
}
