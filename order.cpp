#include "order.h"

   
    Order::Order (std::istream& ist){
      int value;std::string header1,header2;
      ist >> id_number; ist.ignore();
      ist >> value;ist.ignore();
      ist >> cost;ist.ignore();
      ist >> price;ist.ignore();
      std::getline(ist, header1);
      std::getline(ist, header2);
      if (header1 != "#") throw std::runtime_error("missing # during Order's Customer input ");
      if (header2 != "Customer") throw std::runtime_error("missing CUSTOMER during Order input ");
      customer = Customer{ist};

      std::getline(ist, header1);
      std::getline(ist, header2);
      if (header1 != "#") throw std::runtime_error("missing # during Order's Server input");
      if (header2 != "Server") throw std::runtime_error("missing SERVER during Order input");
      server = Server{ist};

      while (true){
            std::getline(ist, header1); // header
            std::getline(ist, header2);
            if (header1 != "#") throw std::runtime_error("missing # during Order input");
            if (header2 == "END ORDER") break;  // footer
            else if (header2 == "SERVING") servings.push_back(Serving{ist});
            else throw std::runtime_error("invalid serving in Order");
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
      cost+= serving.get_wholesale_cost();
      price+= serving.get_retail_price();
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
    ost << "#" << std::endl << "ORDER" << std::endl; // header
      ost << id_number << ' '
          << state.get_value() << ' ' << cost << ' '
          << price << ' '  ;
      customer.save(ost);
      server.save(ost);
      for (Serving serving : servings){
        serving.save(ost);
      }
    ost << "#" << std::endl << "END ORDER" << std::endl; // header
    }


    /*std::string Order::serving_to_string (int index){
      return servings[index].to_string_serving();
    }*/

