#include "emporium.h"
#include <stdlib.h>
#include "state.h"
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
    std::vector<Order*> Emporium::get_unfilled_orders () {
      std::vector<Order*> unfilled_orders;
      for (Order* order: orders){
        if ( order->get_state_string() == "unfilled") unfilled_orders.push_back(order);
      }
      return unfilled_orders;
    }
    std::vector<Order*> Emporium::get_filled_orders () {
      std::vector<Order*> filled_orders;
      for (Order* order: orders){
        if ( order->get_state_string() == "filled") filled_orders.push_back(order);
      }
      return filled_orders;
    }
    std::vector<Order*> Emporium::get_canceled_orders () {
      std::vector<Order*> canceled_orders;
      for (Order* order: orders){
        if ( order->get_state_string() == "canceled") canceled_orders.push_back(order);
      }
      return canceled_orders;
    }
    std::vector<Order*> Emporium::get_unfilled_orders_for_customer (Person* person_ptr) {
      std::vector<Order*> unfilled_orders;
      for (Order* order: orders){
        if ( order->get_state_string() == "unfilled" && order->get_customer() == *person_ptr) unfilled_orders.push_back(order);
      }
      return unfilled_orders;
    }


    std::vector<Person*> Emporium::get_active_persons () {
      std::vector<Person*> pers ;
      for (Person* person : persons){
        if (person->get_active() == true){
          pers.push_back(person);
        }
      }
     return pers;
    }
   void Emporium::set_active_person (int index, bool active){
     persons[index]->set_active(active);
   }


    std::string Emporium::scoop_to_string(int index) {return classify_type<std::vector<Item*>>(get_items(),"Scoop")[index]->to_string();}
    std::string Emporium::container_to_string(int index) {return classify_type<std::vector<Item*>>(get_items(),"Container")[index]->to_string();}
    std::string Emporium::topping_to_string(int index){return classify_type<std::vector<Item*>>(get_items(),"Topping")[index]->to_string();}
    std::string Emporium::servings_to_string (int order_index) {
       std::string result = "";
       int i = 0;
       for (Serving serving : orders[order_index]->get_servings()){
          result += "## Serving "+ std::to_string(i) +" ##"+ "\n";
          result += serving.to_string_serving();
          result += "\n\n";
          i++;
       }
       return result;
    }


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
    int Emporium::number_of_orders() {
      return orders.size();
    }

    void Emporium::restock_item(int index , int amount){
      items[index]->restock(amount);
    }

    void Emporium::fill_order (int index, Server* server_ptr){
     //consume and deduct cash register from item
     std::vector<Order*> unfilled_orders = get_unfilled_orders();
     std::vector<Serving> servings = unfilled_orders[index]->get_servings();
     for (Item* item_ptr : items){
       for (Serving serving: servings){
         Container container = serving.get_container();
         if (*item_ptr == container){
           item_ptr -> consume();
           *cash_register_ptr-= *item_ptr;
         }
         std::vector<Scoop> scoops = serving.get_scoops();
         for (Scoop scoop: scoops){
           if (*item_ptr == scoop){
             item_ptr -> consume();
             *cash_register_ptr-= *item_ptr;
           }
         }
         std::vector<Topping> tops = serving.get_toppings();
         for (Topping top: tops){
           if (*item_ptr == top){
             item_ptr -> consume();
             *cash_register_ptr-= *item_ptr;
           }
         }
      }
     }
     server_ptr->add_order_filled();
     //c-=server if fill==10
     if (server_ptr -> get_num_order_filled() == 10){
        *cash_register_ptr-=*server_ptr;
        server_ptr-> reset_num_order_filled();
     }
     unfilled_orders[index]->fill(server_ptr);
    }

    void Emporium::cancel_order (int index, Person* person_ptr){
       //need to update feature show order for customer only
       std::vector<Order*> unfilled_orders = get_unfilled_orders();
       unfilled_orders[index]->cancel();
    }
    void Emporium::pay_order (int index, Person* person_ptr){
       std::vector<Order*> filled_orders = get_filled_orders();
       filled_orders[index]->pay();
       *cash_register_ptr+=*filled_orders[index];
    }

    void Emporium::save(std::ostream& ost) {
      ost << "#" << std::endl << "EMPORIUM" << std::endl; // header
      //ost << name << std::endl;
      //ost << cash_register << std::endl;
     // ost << id << std::endl;

      for (Item* item_ptr : items){
        item_ptr->save(ost);
      }
      for (Person* person_ptr : persons){
        person_ptr->save(ost);
      }
      for (Order* order_ptr: orders){
        order_ptr->save(ost);
      }
      dirty = false;
      ost << "#" << std::endl << "END EMPORIUM" << std::endl; // footer

    }

    void Emporium::load(std::istream& ist) {
      clear();
      std::string header1, header2;

      std::getline(ist, header1); // header
      std::getline(ist, header2);
      if (header1 != "#") throw std::runtime_error("No Emporium records in file");
      if (header2 != "EMPORIUM") throw std::runtime_error("Malformed Emporium record");

      while(ist) {
        std::getline(ist, header1); // header
        std::getline(ist, header2);
        if (header1 != "#") throw std::runtime_error("missing # during input");
        if (header2 == "Container") items.push_back(new Container{ist});
        else if (header2 == "Scoop") items.push_back(new Scoop{ist});
        else if (header2 == "Topping") items.push_back(new Topping{ist});
        else if (header2 == "ORDER") orders.push_back(new Order{ist});
        else if (header2 == "Server") persons.push_back(new Server{ist});
        else if (header2 == "Customer") persons.push_back(new Customer{ist});
        else if (header2 == "Owner") persons.push_back(new Owner{ist});
        else if (header2 == "Manager") persons.push_back(new Manager{ist});

        else if (header2 == "END EMPORIUM") break;
        else throw std::runtime_error("invalid item type in Emporium");
      }
    }

    void Emporium::new_order ( std:: istream& ist){
       orders.push_back(new Order(ist));
    }

  void Emporium::new_item_person (std::istream& ist, std::string type) {

  }

    void Emporium::clear () {
      for (Item* item: items){
        delete item;
      }
      for (Person* person: persons){
        delete person;
      }
      for (Order* order: orders){
        delete order;
      }
      items.clear();
      persons.clear();
      orders.clear();
    }


    void Emporium::auto_add() {
      //add sample to choose from
      add_scoop(new Scoop ("Vanilla","General",.5,1));
      add_scoop(new Scoop ("Cookies", "Sweet",.5,1));
      add_scoop(new Scoop ("Strawberry", "Chunks of strawberry wrapped in vanilla ice cream", 0.20, 0.50));

      add_top(new Topping ("Whipped Cream","General",.1,.2,0));
      add_top(new Topping ("Chocolate Sauce", "Sweet",.1,.25,0));
      add_top(new Topping ("Cherry", "Classic marichino cherry", 0.1, 0.2, 0));

      add_container(new Container ("Cup","General",.35,.75,3));
      add_container(new Container ("Bowl", "Sweet",1,1,5));  
      add_container(new Container ("Cone", "Crispy airy delight", 0.25, 0.50, 1));
      
      //Create Person
      //  Server (std::string na, int id, double sal)
      add_server (new Server("D-Server",1,11));
      add_server (new Server("Henry Jackson", 2, 15.00));
      //Customer (std::string na, int id, std::string ph)
      add_customer (new Customer ("D-Customer", 1, "6829999999"));
      add_customer (new Customer ("Elton John", 2, "817-555-1313"));
      //Create serving
      //Serving(Container con,std::vector<Scoop> scos,std::vector<Topping> tops) ;
      std::vector<Scoop> scoops = {Scoop ("Strawberry","Chunks of strawberry wrapped in vanilla ice cream", 0.2,.5),Scoop ("Cookies", "Sweet",.5,1)};
      std::vector<Topping> tops = {Topping("Whipped Cream","General",1,1,1), Topping("Chocolate Sauce", "Sweet",1,1,1) };
      Serving serving0 ( Container ("Cup","General",1,1,1), scoops, tops );
       
      //add order 
      Server server ("Duy",1,100);
      Order* order_ptr = new Order (1,server);
      order_ptr->add_serving(serving0);
      add_order(order_ptr);      
    }
