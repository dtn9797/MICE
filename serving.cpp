#include "serving.h"

    Container Serving::get_container () {return container;}
    std::vector<Scoop> Serving::get_scoops (){return scoops;}
    std::vector<Topping> Serving::get_toppings(){return toppings;}
    double Serving::get_wholesale_cost(){return wholesale_cost;}
    double Serving::get_retail_price(){return retail_price;}

    void Serving::add_scoop(Scoop sco) {
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


