#include "serving.h"
#include <sstream>

    Serving::Serving(std::istream& ist){
      std::string header1,header2;
      ist >> wholesale_cost; ist.ignore();
      ist >> retail_price; ist.ignore();
      while (true){
        std::getline(ist, header1); // header
        std::getline(ist, header2);
        if (header1 != "#") throw std::runtime_error("missing # during input");
        if (header2 == "END SERVING") break;  // footer
        else if (header2 == "Container") container = Container{ist};
        else if (header2 == "Scoop") scoops.push_back(Scoop{ist});
        else if (header2 == "Topping") toppings.push_back(Topping{ist});
        else throw std::runtime_error("invalid item type in Serving");       
      }
    }

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
    std::vector<Scoop> Serving::get_scoops() {return scoops;}
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

    void Serving::save(std::ostream& ost) {
    ost << "#" << std::endl << "SERVING" << std::endl; // header
    ost << wholesale_cost << ' ' << retail_price << ' ' ;
      container.save(ost);
      for (Scoop scoop : scoops){       
	scoop.save(ost);
      }
      for (Topping topping : toppings) {
        topping.save(ost);
      }
    ost << "#" << std::endl << "END SERVING" << std::endl; // footer
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

