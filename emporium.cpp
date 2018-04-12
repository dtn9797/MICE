#include "emporium.h"

    void Emporium::add_scoop(Scoop* scoop) {items.push_back(scoop);}
    void Emporium::add_top(Topping* top) {items.push_back(top);}
    void Emporium::add_container(Container* con) {items.push_back(con);}
    void Emporium::add_server(Server* server) {persons.push_back(server);}
    void Emporium::add_customer(Customer* customer) {persons.push_back(customer);}

    std::vector<Item*> Emporium::classify_type(std::string type) {
	std::vector<Item*> results={};	
	for (int i=0 ; i< number_of_items(); i++) {
  	  if (items[i]->type() == type)
	    results.push_back (items[i]);
	}
	return results;
    }

    std::string Emporium::item_to_string(int index) {return items[index]->to_string();}


    std::string Emporium::scoop_to_string(int index) {return classify_type("Scoop")[index]->to_string();}
    std::string Emporium::container_to_string(int index) {return classify_type("Container")[index]->to_string();}
    std::string Emporium::topping_to_string(int index){return classify_type("Topping")[index]->to_string();}

    int Emporium::number_of_items() {items.size();}
    int Emporium::number_of_scoops() {
      std::vector<Item*> results= classify_type("Scoop");
      return results.size();
    }
    int Emporium::number_of_containers() {
      std::vector<Item*> results= classify_type("Container");
      return results.size();
    }
    int Emporium::number_of_toppings() {
      std::vector<Item*> results= classify_type("Topping");
      return results.size();
    }

    void Emporium::auto_add() {
      add_scoop(new Scoop ("Vanilla","General",1,1));
      add_scoop(new Scoop ("Cookies", "Sweet",1,1));

      add_top(new Topping ("Light","General",1,1,1));
      add_top(new Topping ("Normal", "Sweet",1,1,1));

      add_container(new Container ("Cups","General",1,1,1));
      add_container(new Container ("Bowls", "Sweet",1,1,1));       
    }
