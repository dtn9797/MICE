#include "emporium.h"
#include "scoop.h"
#include "test_emporium.h"
#include <vector>

bool test_emporium () {
  Emporium em;
  //auto add items
  em.auto_add();
  //need to write test for emporium
  std::string expected = "";
  bool passed = true; // Optimist!
  //
  // Test constructor
  //
 // if (em.serving)

 // Test order_to_strings
  std::vector<std::string> record = em.order_to_strings(0);
  return true;
}
