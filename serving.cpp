#include "serving.h"
#include <sstream>
    Serving::Serving(Container con,std::vector<Scoop> scos,std::vector<Topping> tops):container{con}{
       wholesale_cost+= con.get_wholesale_cost();
       retail_price+= con.get_retail_price();      
       for (Scoop scoop : scos){ add_scoop(scoop);}
       for (Topping top : tops){ add_top(top);}
    }


    Container Serving::get_container () {return container;}
    Scoop Serving::get_scoop (int index){return scoops[index];}
    Topping Serving::get_topping(int index){return toppings[index];}
    double Serving::get_wholesale_cost(){return wholesale_cost;}
    double Serving::get_retail_price(){return retail_price;}
    int Serving::get_number_scoops(){return scoops.size();}
    int Serving::get_number_toppings(){return toppings.size();}
    std::vector<Scoop> Serving::get_scoops () {return scoops;}
    std::vector<Topping> Serving::get_toppings() {return toppings;}
    void Serving::add_scoop(Scoop sco) {
      //if it reachs its limit
      wholesale_cost+= sco.get_wholesale_cost();
      retail_price+= sco.get_retail_price();
      scoops.push_back(sco); 
    }
    void Serving::add_top(Topping top) {
      wholesale_cost+= top.get_wholesale_cost();
      retail_price+= top.get_retail_price();       
      toppings.push_back(top); 
    }

    void Serving::remove_scoop(int index) {
      wholesale_cost-=scoops[index].get_wholesale_cost();
      retail_price-=  scoops[index].get_retail_price();      
      scoops.erase(scoops.begin()+index);
    } 
    void Serving::remove_top(int index)   {
      wholesale_cost-= toppings[index].get_wholesale_cost();
      retail_price-= toppings[index].get_retail_price();
      toppings.erase(toppings.begin()+index);
    }
    void Serving::replace_container(Container con) {
      wholesale_cost-= container.get_wholesale_cost();
      retail_price-= container.get_retail_price();
      wholesale_cost+= con.get_wholesale_cost();
      retail_price+= con.get_retail_price();      
      container = con;
    }
    std::string Serving::to_string_serving(){
      std::stringstream buffer;
      buffer << "Container:" << std:: endl;
      buffer<<'\t'<< container.get_name() << ','
            << container.get_description() << ','
            << "Limit:" << container.get_scoop_limit() <<std:: endl;
      buffer<<"Scoop(s):" << std:: endl;
     for(Scoop scoop:scoops){
      buffer<<'\t'<< scoop.get_name() << ','
            << scoop.get_description() << std:: endl;
     }
      buffer<<"Topping(s):" << std:: endl;
     for(Topping topping:toppings){
      buffer<<'\t'<< topping.get_name() << ','
            << topping.get_description() << ','
            << topping.to_string_amount()<< std:: endl;
     }
      buffer<<"Price: $" << get_retail_price() << std:: endl;
      buffer<<"Cost: $" << get_wholesale_cost() << std:: endl;
      return buffer.str();
    }

