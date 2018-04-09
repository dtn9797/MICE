
#include "test_emporium.h"
#include "test_view.h"
#include "test_scoop.h"
#include "test_container.h"
#include "test_topping.h"
#include <iostream>

int main() {
  if (!(test_topping() && test_scoop() && test_container() && test_emporium()))
    std::cerr << "fail" << std::endl;
} 
