#include "order.h"


    void Order::fill(Server &server) {
      state = State:: filled;
      server.add_order_filled();
    }
    void Order::pay(){ state = State:: paid;}
    void Order::cancel() {state= State:: canceled;}

    void Order::add_serving(Serving& serving) {
      servings.push_back(serving);
      cost+= serving.get_retail_price();
      price+= serving.get_wholesale_cost();
    }

    int Order::get_id_number () {return id_number;}
    std::vector<Serving> Order::get_servings(){return servings;}
    State Order::get_state(){return state;}
    double Order::get_cost(){return cost;}
    double Order::get_price(){return price;}
    Server Order::get_server(){return server;}
    Customer Order::get_customer(){return customer;}

    int Order::number_of_servings() { return servings.size();}

    /*std::string Order::serving_to_string (int index){
      return servings[index].to_string_serving();
    }*/

    std::vector<std::string> Order::to_strings(){
      std::vector<std::string> order;
      order.push_back(std::to_string(id_number));
      order.push_back(server.get_name());
      order.push_back(customer.get_name());
      order.push_back(state.to_string());
      order.push_back(std::to_string(price));
      return order;
    }
