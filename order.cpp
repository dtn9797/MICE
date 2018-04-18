#include "order.h"




    int Order::get_id_number () {return id_number;}
    std::vector<Serving> Order::get_servings(){return servings;}
    State Order::get_state(){return state;}
    double Order::get_cost(){return cost;}
    double Order::get_price(){return price;}

    int Order::number_of_servings() { return servings.size();}

    /*std::string Order::serving_to_string (int index){
      return servings[index].to_string_serving();
    }*/

    std::vector<std::string> Order::to_strings(){
      std::vector<std::string> order;
      order.push_back(std::to_string(id_number));
      order.push_back(state.to_string());
      order.push_back(std::to_string(price));
      return order;
    }
