
#include "test_items_scoop_container_topping.h"
#include "test_emporium.h"
#include "test_view.h"
#include <iostream>

int main() {
  if (!(test_items_scoop_container_topping() && test_view() && test_emporium()))
    std::cerr << "fail" << std::endl;
} 
