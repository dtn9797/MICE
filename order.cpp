#include "order.h"

   
    Order::Order (std::istream& ist){
      int value;
      ist >> id_number >> value >> cost >> price;
      while (ist){
        std::string type;
        int len = ist.tellg();
        std::getline (ist, type); 
        if (type == "Serving") {
          servings.push_back(Serving(ist));
        }
        else if (type == "Customer"){
          customer = Customer(ist);
        }
        else if (type == "Server"){
          server = Server (ist);
        }
        else if (type == " " || type == "\n" || type == " \n"){
           continue;
        }
        else {
         ist.seekg(len,std::ios_base::beg);
         break;
        }  
      }  
      switch(value) {
         case(0):state= State::unfilled;break;
         case(1):state= State::filled;break;
         case(2):state= State:: paid;break;
         case(3):state= State::canceled;break;
       }
    }
 

    void Order::fill(Server *server_ptr) {
      state = State:: filled;
      server = *server_ptr;
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
    std::string Order::get_state_string (){return state.to_string();}
    double Order::get_cost(){return cost;}
    double Order::get_price() const {return price;}
    Server Order::get_server(){return server;}
    Customer Order::get_customer(){return customer;}

    int Order::number_of_servings() { return servings.size();}

    void Order::save(std::ostream& ost){
      ost << "Order" << std::endl;
      ost << id_number << ' '
          << state.get_value() << ' ' << cost << ' '
          << price ;
      for (Serving serving : servings){
        serving.save(ost);
        ost<<std::endl;
      }
      server.save(ost);
      ost<<std::endl;
      customer.save(ost);
    }


    /*std::string Order::serving_to_string (int index){
      return servings[index].to_string_serving();
    }*/

