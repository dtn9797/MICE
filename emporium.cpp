#include "emporium.h"
#include <stdlib.h>
    void Emporium::add_scoop(Scoop* scoop) {items.push_back(scoop);}
    void Emporium::add_top(Topping* top) {items.push_back(top);}
    void Emporium::add_container(Container* con) {items.push_back(con);}
    void Emporium::add_server(Server* server) {persons.push_back(server);}
    void Emporium::add_customer(Customer* customer) {persons.push_back(customer);}
    void Emporium::add_owner(Owner* owner) {persons.push_back(owner);}
    void Emporium::add_manager(Manager* manager) {persons.push_back(manager);}
    void Emporium::add_order (Order* order) {orders.push_back(order);}

    std::string Emporium::item_to_string(int index) {return items[index]->to_string();}

    std::vector<Item*>  Emporium::get_items () {return items;}
    std::vector<Person*>  Emporium::get_persons () {return persons;}
    std::vector<Order*>  Emporium::get_orders () {return orders;}
    Person* Emporium::get_active_person () {
      for (Person* person : persons){
        if (person->get_active() == true){
          return person;   
        }
      }
    }
   void Emporium::set_active_person (int index){
     for (Person* person: persons){
       person->set_active(false);
     }
     persons[index]->set_active(true);
   }


    std::string Emporium::scoop_to_string(int index) {return classify_type<std::vector<Item*>>(get_items(),"Scoop")[index]->to_string();}
    std::string Emporium::container_to_string(int index) {return classify_type<std::vector<Item*>>(get_items(),"Container")[index]->to_string();}
    std::string Emporium::topping_to_string(int index){return classify_type<std::vector<Item*>>(get_items(),"Topping")[index]->to_string();}

    int Emporium::number_of_items() {items.size();}
    int Emporium::number_of_scoops() {
      std::vector<Item*> results= classify_type<std::vector<Item*>>(get_items(),"Scoop");
      return results.size();
    }
    int Emporium::number_of_containers() {
      std::vector<Item*> results= classify_type<std::vector<Item*>>(get_items(),"Container");
      return results.size();
    }
    int Emporium::number_of_toppings() {
      std::vector<Item*> results= classify_type<std::vector<Item*>>(get_items(),"Topping");
      return results.size();
    }

    void Emporium::auto_add() {
      //add sample to choose from
      add_scoop(new Scoop ("Vanilla","General",1,1));
      add_scoop(new Scoop ("Cookies", "Sweet",1,1));

      add_top(new Topping ("Whipped Cream","General",1,1,1));
      add_top(new Topping ("Chocolate Sauce", "Sweet",1,1,1));

      add_container(new Container ("Cup","General",1,1,1));
      add_container(new Container ("Bowl", "Sweet",1,1,1));  
      
      //Create Person
      //  Server (std::string na, int id, double sal)
      add_server (new Server("Server",1,11));
      //Customer (std::string na, int id, std::string ph)
      add_customer (new Customer ("Customer", 1, "6829999999"));
      //Create serving
      //Serving(Container con,std::vector<Scoop> scos,std::vector<Topping> tops) ;
      std::vector<Scoop> scoops = {Scoop ("Vanilla","General",1,1),Scoop ("Cookies", "Sweet",1,1)};
      std::vector<Topping> tops = {Topping("Whipped Cream","General",1,1,1), Topping("Chocolate Sauce", "Sweet",1,1,1) };
      Serving serving ( Container ("Cup","General",1,1,1), scoops, tops );
      //add order 
      //Order (int id, Server &ser): id_number{id} ,server{ser}{}
      Order order0(1,*(dynamic_cast<Server*>(persons[2])));
      order0.add_serving(serving); 
      add_order(&order0);  
      
    }
