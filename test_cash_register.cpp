#include <iostream>
#include "cash_register.h"

bool cash_register() {
  std::string expected = "";
  bool passed = true; // Optimist!

  //
  // Test constructor
  //
  Cash_register c(2000);
  if (c.get_amount!=2000){
    std::cerr << "Cash register Constructor failed !";
    passed = false;
  }

  return true;


}
