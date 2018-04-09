#include "view.h"
#include <string>
#include <iostream>
using namespace std;
void View::show_menu (){
    string menu = R"(
=================================
CSE1325 Emporium Management System
=================================

Ice cream flavors
------------
(1) Add a flavor
(2) List all Ice cream flavors

Containers
------------
(3) Add a container
(4) List all containers

Toppings
------------
(5) Add a topping
(6) List all toppings

Utility
-------
(0) Exit

)";

  cout << menu;
}

void View::list_scoops (){
    string header = R"(
----------------------------
List of Ice Cream Flavors
----------------------------
)";
  cout << header;
  for (int i=0; i<emporium.number_of_scoops(); ++i) {
    cout << i << ") " << emporium.scoop_to_string(i) << endl;
  }
}

void View::list_containers() {
      string header = R"(
----------------------------
    List of Containers
----------------------------
)";
  cout << header;
  for (int i=0; i<emporium.number_of_containers(); ++i) {
    cout << i << ") " << emporium.container_to_string(i) << endl;
  }
}

void View::list_toppings(){
        string header = R"(
----------------------------
    List of Toppings
----------------------------
)";
  cout << header;
  for (int i=0; i<emporium.number_of_toppings(); ++i) {
    cout << i << ") " << emporium.topping_to_string(i) << endl;
  }
}

void View::show_create_item_dialog(){
    int type;

    Gtk::Dialog *dialog = new Gtk::Dialog();
    dialog->set_title("Create Item");
    //Type
    Gtk::HBox b_type;

    Gtk::Label l_type{"Type:"};
    l_type.set_width_chars(15);
    b_type.pack_start(l_type, Gtk::PACK_SHRINK);

    Gtk::ComboBoxText c_type;
    c_type.set_size_request(160);
    c_type.append("Container");
    c_type.append("Ice Cream Flavor");
    c_type.append("Topping");
    b_type.pack_start(c_type, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_type, Gtk::PACK_SHRINK);     

    // Show dialog
    dialog->add_button("Cancel", 0);
    dialog->add_button("OK", 1);
    dialog->show_all();
    int result = dialog->run();

    dialog->close();
    while (Gtk::Main::events_pending())  Gtk::Main::iteration();

    if (result == 1){
      type = c_type.get_active_row_number();
      //type = 1: Containter , 2: Ice Cream Flavor, 3: Topping
      std::map <int,std::string> type_name= {{0,"Container"},{1,"Ice Cream Flavor"},{2,"Topping"}};
      create_chosen_type_dialog(type_name[type]);
    }
}


//PRIVATE FUNCTIONS


void View::create_chosen_type_dialog(std::string type_name){
    Gtk::Dialog *dialog = new Gtk::Dialog();
    dialog->set_title("Create "+type_name);

    std::string name,description;
    double wholesale_cost, retail_price;
    int limit = 0;
   
    //Name 
    Gtk::HBox b_name;

    Gtk::Label l_name{"Name:"};
    l_name.set_width_chars(15);
    b_name.pack_start(l_name, Gtk::PACK_SHRINK);

    Gtk::Entry e_name;
    e_name.set_max_length(50);
    b_name.pack_start(e_name, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_name, Gtk::PACK_SHRINK);
    
    //Description
    Gtk::HBox b_description;

    Gtk::Label l_description{"Description:"};
    l_description.set_width_chars(15);
    b_description.pack_start(l_description, Gtk::PACK_SHRINK);

    Gtk::Entry e_description;
    e_description.set_max_length(50);
    b_description.pack_start(e_description, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_description, Gtk::PACK_SHRINK);

    //Wholesale_cost
    Gtk::HBox b_wholesale_cost;

    Gtk::Label l_wholesale_cost{"Wholesale Cost:"};
    l_wholesale_cost.set_width_chars(15);
    b_wholesale_cost.pack_start(l_wholesale_cost, Gtk::PACK_SHRINK);

    Gtk::Entry e_wholesale_cost;
    e_wholesale_cost.set_max_length(50);
    b_wholesale_cost.pack_start(e_wholesale_cost, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_wholesale_cost, Gtk::PACK_SHRINK);

    // Retail_price
    Gtk::HBox b_retail_price;

    Gtk::Label l_retail_price{"Retail Price:"};
    l_retail_price.set_width_chars(15);
    b_retail_price.pack_start(l_retail_price, Gtk::PACK_SHRINK);

    Gtk::Entry e_retail_price;
    e_retail_price.set_max_length(50);
    b_retail_price.pack_start(e_retail_price, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_retail_price, Gtk::PACK_SHRINK);
    
    if (type_name == "Container"){
     // Scoop limit
     Gtk::HBox b_scoop_limit;

     Gtk::Label l_scoop_limit{"Retail Price:"};
     l_scoop_limit.set_width_chars(15);
     b_scoop_limit.pack_start(l_scoop_limit, Gtk::PACK_SHRINK);

     Gtk::Entry e_scoop_limit;
     e_scoop_limit.set_max_length(50);
     b_scoop_limit.pack_start(e_scoop_limit, Gtk::PACK_SHRINK);
     dialog->get_vbox()->pack_start(b_scoop_limit, Gtk::PACK_SHRINK);
    }

    // Show dialog
    dialog->add_button("Cancel", 0);
    dialog->add_button("OK", 1);
    dialog->show_all();
    int result = dialog->run();

    dialog->close();
    while (Gtk::Main::events_pending())  Gtk::Main::iteration();
    if ( result == 0) { show_create_item_dialog();return;}

    name = e_name.get_text();
    description = e_description.get_text();
    wholesale_cost = std::stod (e_wholesale_cost.get_text());
    retail_price = std::stod (e_retail_price.get_text());

    if(result==1){
      if (type_name == "Container") emporium.add_container(new Container(name, description,wholesale_cost,retail_price,0));
      else if (type_name == "Ice Cream Flavor")emporium.add_scoop(new Scoop(name, description,wholesale_cost,retail_price));
      else if (type_name == "Topping") emporium.add_top(new Topping(name, description,wholesale_cost,retail_price));
      show_create_item_dialog();
    }


}
