#include "view.h"
#include <string>
#include <iostream>
#include <stdlib.h>
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

//GUI

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

void View::show_create_serving_dialog(){
    int container;

    Gtk::Dialog *dialog = new Gtk::Dialog();
    dialog->set_title("Create Serving");
    // Add Container
    Gtk::HBox b_container;

    Gtk::Label l_container{"Container:"};
    l_container.set_width_chars(15);
    b_container.pack_start(l_container, Gtk::PACK_SHRINK);

    Gtk::ComboBoxText c_container;
    c_container.set_size_request(160);
    vector<Item*> containers = emporium.classify_type("Container");
    for (Item* container : containers){
      std::string container_info = container -> get_name ()+"," + container->get_description() + "(Scoop Limit: " +std::to_string(dynamic_cast<Container*>(container)->get_scoop_limit())+')';
      c_container.append(container_info);
    }

    b_container.pack_start(c_container, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_container, Gtk::PACK_SHRINK);  
 
    //b_container.set_margin_left(105);
    //Button:  button.signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_create_item_click))
   
    // Show dialog
    dialog->add_button("Cancel", 0);
    dialog->add_button("Add Container", 1);
    dialog->show_all();
    int result = dialog->run();

    dialog->close();
    while (Gtk::Main::events_pending())  Gtk::Main::iteration();   

    if (result == 1){
       int index  = c_container.get_active_row_number();
       //add container to serving
       Container* container_ptr = dynamic_cast<Container*>(containers[index]);
       Serving serving (*container_ptr, std::vector<Scoop> (),std::vector<Topping> () );
       int scoop_limit = container_ptr->get_scoop_limit();
       create_scoop_for_serving (serving,0,scoop_limit);
    }

}

//
//PRIVATE FUNCTIONS
//

//Scoop for Serving
void View::create_scoop_for_serving (Serving& serving, int scoop_amount, int scoop_limit) {
    //Design
    Gtk::Dialog *dialog = new Gtk::Dialog();
    dialog->set_title("Create Serving");

    Gtk::HBox b_scoop;

    Gtk::Label l_scoop{"Scoop:"};
    l_scoop.set_width_chars(15);
    b_scoop.pack_start(l_scoop, Gtk::PACK_SHRINK);

    Gtk::ComboBoxText c_scoop;
    c_scoop.set_size_request(160);

    vector<Item*> scoops = emporium.classify_type("Scoop");
    for (Item* scoop : scoops){
      std::string scoop_info = scoop -> get_name ()+"," + scoop->get_description() + "(Price: " +std::to_string(scoop->get_retail_price())+')';
      c_scoop.append(scoop_info);
    }

    b_scoop.pack_start(c_scoop, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_scoop, Gtk::PACK_SHRINK);  

    // Show dialog
    dialog->add_button("Cancel", 0);
    if (scoop_amount > 0){ dialog->add_button("Complete Order",1);}
    dialog->add_button("Add Scoop", 2);
    dialog->add_button("Add Topping", 3);
    dialog->show_all();
    int result = dialog->run();

    dialog->close();
    while (Gtk::Main::events_pending())  Gtk::Main::iteration();   
    if (result ==0 )return;
    int index = c_scoop.get_active_row_number();
    Scoop* scoop =  dynamic_cast<Scoop*>(scoops[index]);
    if (result == 2){
       if (scoop_amount+1 >= 0  && scoop_amount+1 <= scoop_limit){
         serving.add_scoop(*scoop);
         scoop_amount+=1;
         create_scoop_for_serving (serving,scoop_amount,scoop_limit);
       }
       else{ 
         create_message_dialog ("Error","Container reaches scoop limit if adding one more scoop.");
         create_scoop_for_serving (serving,scoop_amount,scoop_limit);
       }
    }
    else if (result==3){
       scoop_amount+=1;
       serving.add_scoop(*scoop);
       //create_topping_for_serving(serving);
    }
    else if (result ==1 ){
       serving.add_scoop(*scoop);
    }

}
/*
//Topping for Serving
void View::create_topping_for_serving () {
    //Design

    // Show dialog
    dialog->add_button("Cancel", 0);
    dialog->add_button("Complete Serving", 1);
    dialog->add_button("Add Scoop", 2);
    dialog->add_button("Add Topping", 3);

    dialog->show_all();
    int result = dialog->run();

    dialog->close();
    while (Gtk::Main::events_pending())  Gtk::Main::iteration();   

    if (result == 2){
       if (//scoop not reach limit)
         create_scoop_for_serving (int scoop_limit);
       else 
         create_message_dialog (std::string message);
    }
    else if (result==3){
       create_topping_for_serving();
    }
    else if (result==1){
       //Add topping to order
    }
}

*/

//Dialog
void View::create_message_dialog(std::string title, std::string msg) {
    Gtk::MessageDialog *dialog = new Gtk::MessageDialog(title);
    dialog->set_secondary_text(msg, true);
    dialog->run();

    dialog->close();
    while (Gtk::Main::events_pending())  Gtk::Main::iteration();

    delete dialog;
}

//Emporium
void View::create_chosen_type_dialog(std::string type_name){
    Gtk::Dialog *dialog = new Gtk::Dialog();
    dialog->set_title("Create "+type_name);

    std::string name,description;
    double wholesale_cost, retail_price;
    int limit = 0; int amount = 1;
   
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
    
    Gtk::Entry e_scoop_limit;
    if (type_name == "Container"){
     // Scoop limit
     Gtk::HBox b_scoop_limit;

     Gtk::Label l_scoop_limit{"Retail Price:"};
     l_scoop_limit.set_width_chars(15);
     b_scoop_limit.pack_start(l_scoop_limit, Gtk::PACK_SHRINK);

     e_scoop_limit.set_max_length(50);
     b_scoop_limit.pack_start(e_scoop_limit, Gtk::PACK_SHRINK);
     dialog->get_vbox()->pack_start(b_scoop_limit, Gtk::PACK_SHRINK);
    }
    Gtk::ComboBoxText c_amount;
    if (type_name == "Topping"){
    //Amount of topping
    Gtk::HBox b_amount;

    Gtk::Label l_amount{"Amount:"};
    l_amount.set_width_chars(15);
    b_amount.pack_start(l_amount, Gtk::PACK_SHRINK);

    c_amount.set_size_request(160);
    c_amount.append("Light");
    c_amount.append("Normal");
    c_amount.append("Extra");
    c_amount.append("Drenched");
    b_amount.pack_start(c_amount, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_amount, Gtk::PACK_SHRINK);     
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
    wholesale_cost = atof (e_wholesale_cost.get_text().c_str());
    retail_price = atof (e_retail_price.get_text().c_str());
    limit =atoi(e_scoop_limit.get_text().c_str());
    amount =c_amount.get_active_row_number()+1;

    if(result==1){
      if (type_name == "Container") emporium.add_container(new Container(name, description,wholesale_cost,retail_price,limit));
      else if (type_name == "Ice Cream Flavor")emporium.add_scoop(new Scoop(name, description,wholesale_cost,retail_price));
      else if (type_name == "Topping") emporium.add_top(new Topping(name, description,wholesale_cost,retail_price,amount));
      show_create_item_dialog();
    }

}
