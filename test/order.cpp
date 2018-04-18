#include "order.h"

    std::vector<std::string> Order::to_strings(){
      std::vector<std::string> order;
      order.push_back(std::to_string(id_number));
      order.push_back(state.to_string());
      order.push_back(std::to_string(price));
      return order;
    }
