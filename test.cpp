
#include "test_emporium.h"
#include "test_view.h"
#include "test_scoop.h"
#include "test_container.h"
#include "test_topping.h"
#include "test_serving.h"
#include "test_person.h"
#include "test_server.h"
#include "test_customer.h"
#include "test_order.h"
#include <iostream>

int main() {
  if (!(test_topping() && test_scoop() && test_container() && test_serving() &&test_emporium() && test_person() && test_customer() && test_server() && test_order()))
    std::cerr << "fail" << std::endl;
} 
