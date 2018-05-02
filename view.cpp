#include "view.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <exception>
#include <stdexcept>
#include <regex>

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
///////////////////
///////////GUI//////
//////////////////////
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
    if (result !=0 && c_type.get_active_row_number() == -1) throw runtime_error ("Need to choose a type first");
    if (result == 1){
      type = c_type.get_active_row_number();
      //type = 1: Containter , 2: Ice Cream Flavor, 3: Topping
      std::map <int,std::string> type_name= {{0,"Container"},{1,"Ice Cream Flavor"},{2,"Topping"}};
      create_chosen_type_dialog(type_name[type]);
    }
}
//WARNING CHANGE DIALOG
void View::show_create_serving_dialog(Order* order_ptr){
    int container;
    Gtk::Dialog dialog;
    dialog.set_title("Create Serving");
    // Add Container
    Gtk::HBox b_container;

    Gtk::Label l_container{"Container:"};
    l_container.set_width_chars(15);
    b_container.pack_start(l_container, Gtk::PACK_SHRINK);

    Gtk::ComboBoxText c_container;
    c_container.set_size_request(160);
    vector<Item*> containers = emporium.classify_type<vector<Item*>>(emporium.get_items(),"Container");
    if (containers.size() < 0) throw runtime_error ("No Container To Show");
    for (int i=0 ; i < emporium.number_of_containers();i++){
      std::string container_info = containers[i] -> get_name ()+"," + containers[i]->get_description() + "(Scoop Limit: " +std::to_string(dynamic_cast<Container*>(containers[i])->get_scoop_limit())+')';
      c_container.append(container_info);
    }

    b_container.pack_start(c_container, Gtk::PACK_SHRINK);
    dialog.get_vbox()->pack_start(b_container, Gtk::PACK_SHRINK);  
 
    //b_container.set_margin_left(105);
    //Button:  button.signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_create_item_click))
   
    // Show dialog
    dialog.add_button("Cancel", 0);
    dialog.add_button("Add Container", 1);
    dialog.add_button("Show Image", 2);

    dialog.show_all();
    int result = dialog.run();

    dialog.close();
    while (Gtk::Main::events_pending())  Gtk::Main::iteration();   

    if (c_container.get_active_row_number() == -1 && result!= 0 ) throw runtime_error("Need to select a container first");

    if (result == 1){
       int index  = c_container.get_active_row_number();
       //add container to serving
       Container* container_ptr = dynamic_cast<Container*>(containers[index]);
       Serving serving (*container_ptr, std::vector<Scoop> (),std::vector<Topping> () );
       int scoop_limit = container_ptr->get_scoop_limit();

       create_scoop_for_serving (order_ptr,serving,0,scoop_limit);
    }
   else if (result ==2 ){
       int index = c_container.get_active_row_number();
       std::string image_name = containers[index]->get_image_name();
       Gtk::Image image(image_name);
       create_image_dialog("Container",image);
       show_create_serving_dialog(order_ptr);
    }


}

int View::show_items () {
    int item_index = -1;
    //Design
    Gtk::Dialog dialog;
    dialog.set_title("Items");

    Gtk::HBox b_item;

    Gtk::Label l_item{"Items:"};
    l_item.set_width_chars(15);
    b_item.pack_start(l_item, Gtk::PACK_SHRINK);

    Gtk::ComboBoxText c_item;
    c_item.set_size_request(160);

    vector<Item*> items = emporium.get_items();
    for (Item* item : items){
      std::string item_info = item -> get_name ()+"," + item->get_description() + "(Amount: " +std::to_string(item->get_stock_remaining())+')';
      c_item.append(item_info);
    }

    b_item.pack_start(c_item, Gtk::PACK_SHRINK);
    dialog.get_vbox()->pack_start(b_item, Gtk::PACK_SHRINK);  

    // Show dialog
    dialog.add_button("Cancel", 0);
    dialog.add_button ("OK",1);
    dialog.show_all();
    int result = dialog.run();
    dialog.close();
    if (result == 1 ){
      try {item_index= c_item.get_active_row_number();}
      catch (std::exception e){
        create_message_dialog("Error", "Need to select Item first");
        return -1;
      }     
    }
    return item_index;
} 
int View::show_unfilled_orders () {
    int order_index = -1;
    //Design
    Gtk::Dialog dialog;
    dialog.set_title("Unfilled Orders");

    Gtk::HBox b_order;

    Gtk::Label l_order{"Unfilled Orders:"};
    l_order.set_width_chars(15);
    b_order.pack_start(l_order, Gtk::PACK_SHRINK);

    Gtk::ComboBoxText c_order;
    c_order.set_size_request(160);

    vector<Order*> unfilled_orders = emporium.get_unfilled_orders();
    if (unfilled_orders.size()<=0) throw std:: runtime_error ("No order to show"); 
//    std::cout << "Unfilled_orderr size in view :" << unfilled_orders.size() << std::endl;
    for (Order* unfilled_order : unfilled_orders){
      std::string unfilled_order_info = std::to_string(unfilled_order -> get_id_number())+ "(Price: " +std::to_string(unfilled_order->get_price())+')';
      c_order.append(unfilled_order_info);
    }

    b_order.pack_start(c_order, Gtk::PACK_SHRINK);
    dialog.get_vbox()->pack_start(b_order, Gtk::PACK_SHRINK);  

    // Show dialog
    dialog.add_button("Cancel", 0);
    dialog.add_button ("OK",1);
    dialog.show_all();
    int result = dialog.run();
    dialog.close();
    if (result == 1 ){
      try {order_index= c_order.get_active_row_number();}
      catch (std::exception e){
        create_message_dialog("Error", "Need to select Order first");
        return -1;
      }
    }
    return order_index;
} 
int View::show_filled_orders () {
    int order_index = -1;
    //Design
    Gtk::Dialog dialog;
    dialog.set_title("Filled Orders");

    Gtk::HBox b_order;

    Gtk::Label l_order{"Filled Orders:"};
    l_order.set_width_chars(15);
    b_order.pack_start(l_order, Gtk::PACK_SHRINK);

    Gtk::ComboBoxText c_order;
    c_order.set_size_request(160);

    vector<Order*> filled_orders = emporium.get_filled_orders();
    if (filled_orders.size()<=0) throw std:: runtime_error ("No filled order to show "); 
    for (Order* filled_order : filled_orders){
      std::string filled_order_info = std::to_string(filled_order -> get_id_number())+ "(Price: " +std::to_string(filled_order->get_price())+')';
      c_order.append(filled_order_info);
    }

    b_order.pack_start(c_order, Gtk::PACK_SHRINK);
    dialog.get_vbox()->pack_start(b_order, Gtk::PACK_SHRINK);  

    // Show dialog
    dialog.add_button("Cancel", 0);
    dialog.add_button ("OK",1);
    dialog.show_all();
    int result = dialog.run();
    dialog.close();
    if (result == 1 ){
      try {order_index= c_order.get_active_row_number();}
      catch (std::exception e){
        create_message_dialog("Error", "Need to select Order first");
        return -1;
      }
    }
    return order_index;
} 
int View::show_unfilled_orders_for_customer(Person* person_ptr){
    int order_index = -1;
    //Design
    Gtk::Dialog dialog;
    dialog.set_title("Unfilled Orders");

    Gtk::HBox b_order;

    Gtk::Label l_order{"Unfilled Orders:"};
    l_order.set_width_chars(15);
    b_order.pack_start(l_order, Gtk::PACK_SHRINK);

    Gtk::ComboBoxText c_order;
    c_order.set_size_request(160);

    vector<Order*> unfilled_orders = emporium.get_unfilled_orders_for_customer(person_ptr);
    if (unfilled_orders.size()<=0) throw std:: runtime_error ("No order to show for current customer"); 
//    std::cout << "Unfilled_orderr size in view :" << unfilled_orders.size() << std::endl;
    for (Order* unfilled_order : unfilled_orders){
      std::string unfilled_order_info = std::to_string(unfilled_order -> get_id_number())+ "(Cost: " +std::to_string(unfilled_order->get_cost())+')';
      c_order.append(unfilled_order_info);
    }

    b_order.pack_start(c_order, Gtk::PACK_SHRINK);
    dialog.get_vbox()->pack_start(b_order, Gtk::PACK_SHRINK);  

    // Show dialog
    dialog.add_button("Cancel", 0);
    dialog.add_button ("OK",1);
    dialog.show_all();
    int result = dialog.run();
    dialog.close();
    if (result == 1 ){
      try {order_index= c_order.get_active_row_number();}
      catch (std::exception e){
        create_message_dialog("Error", "Need to select Order first");
        return -1;
      }
    }
    return order_index;
}
//
//PRIVATE FUNCTIONS
//

//Scoop for Serving///WARNING NEW DIALOG
void View::create_scoop_for_serving (Order* order_ptr,Serving& serving, int scoop_amount, int scoop_limit) {
    //Design
    Gtk::Dialog dialog ;
    dialog.set_title("Create Scoop for Serving");

    Gtk::HBox b_scoop;

    Gtk::Label l_scoop{"Scoop:"};
    l_scoop.set_width_chars(15);
    b_scoop.pack_start(l_scoop, Gtk::PACK_SHRINK);

    Gtk::ComboBoxText c_scoop;
    c_scoop.set_size_request(160);

    vector<Item*> scoops = emporium.classify_type<vector<Item*>>(emporium.get_items(),"Scoop");
    for (Item* scoop : scoops){
      std::string scoop_info = scoop -> get_name ()+"," + scoop->get_description() + "(Price: " +std::to_string(scoop->get_retail_price())+')';
      c_scoop.append(scoop_info);
    }

    b_scoop.pack_start(c_scoop, Gtk::PACK_SHRINK);
    dialog.get_vbox()->pack_start(b_scoop, Gtk::PACK_SHRINK);  

    

    // Show dialog
    dialog.add_button("Cancel", 0);
    if (scoop_amount > 0){ dialog.add_button("Complete Serving",1);}
    dialog.add_button("Add Scoop", 2);
    if (scoop_amount != 0)dialog.add_button("Go to Topping", 3);
    dialog.add_button ("Serving Info",4);
    dialog.add_button("Show Image",5);
    dialog.show_all();
    int result = dialog.run();

    dialog.close();
    while (Gtk::Main::events_pending())  Gtk::Main::iteration();   
    if (result ==0 )return;
    if (c_scoop.get_active_row_number() == -1 && (result ==5 || result == 2 )) throw runtime_error ("Need to select a scoop first"); 
    /*      create_message_dialog ("Error","Need to select a scoop first");
         create_scoop_for_serving (order_ptr,serving,scoop_amount,scoop_limit);
    }*/

    if (result == 2){//add scoop
       if (scoop_amount+1 >= 0  && scoop_amount+1 <= scoop_limit){
         int index = c_scoop.get_active_row_number();
         Scoop* scoop =  dynamic_cast<Scoop*>(scoops[index]);
         serving.add_scoop(*scoop);
         scoop_amount=serving.get_number_scoops();
         create_scoop_for_serving (order_ptr,serving,scoop_amount,scoop_limit);
       }
       else{ 
         create_message_dialog ("Error","Container reaches scoop limit if adding one more scoop.");
         create_scoop_for_serving (order_ptr,serving,scoop_amount,scoop_limit);
       }
    }
    else if (result==3){//go to top
       create_topping_for_serving(order_ptr,serving);
    }
    else if (result ==1 ){
       //Need to add : add serving to order
       int answer= question("Do you want to add more serving in order?","Question",{"Yes","No"});
       if (answer == 0 ){ //add serving to order then show dialogs again
         order_ptr->add_serving(serving);
         show_create_serving_dialog(order_ptr);
         
       }
       else if (answer == 1){ //add serving then add order to emporium
         order_ptr->add_serving(serving);
         emporium.add_order(order_ptr);       
       }
    }
    else if (result==4){
       show_serving_info (serving);
       create_scoop_for_serving (order_ptr,serving,scoop_amount,scoop_limit);
    }
    else if (result == 5){
       int index = c_scoop.get_active_row_number();
       std::string image_name = scoops[index]->get_image_name();
       Gtk::Image image(image_name);
       create_image_dialog("Test",image);
       create_scoop_for_serving (order_ptr,serving,scoop_amount,scoop_limit);
    }

}

//Topping for Serving
void View::create_topping_for_serving (Order* order_ptr, Serving& serving) {
    //Design
    Gtk::Dialog *dialog = new Gtk::Dialog();
    dialog->set_title("Create Topping for Serving");
    //Top info
    Gtk::HBox b_top;

    Gtk::Label l_top{"Topping:"};
    l_top.set_width_chars(15);
    b_top.pack_start(l_top, Gtk::PACK_SHRINK);

    Gtk::ComboBoxText c_top;
    c_top.set_size_request(160);

    vector<Item*> tops = emporium.classify_type<vector<Item*>>(emporium.get_items(),"Topping");
    for (Item* top : tops){
      std::string top_info = top -> get_name ()+"," + top->get_description() + "(Price: " +std::to_string(top->get_retail_price())+')';
      c_top.append(top_info);
    }

    b_top.pack_start(c_top, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_top, Gtk::PACK_SHRINK);  
    //Top Amount
    Gtk::HBox b_amount;

    Gtk::Label l_amount{"Topping Amount:"};
    l_amount.set_width_chars(15);
    b_amount.pack_start(l_amount, Gtk::PACK_SHRINK);

    Gtk::ComboBoxText c_amount;
    c_amount.set_size_request(160);

    c_amount.append("Light");
    c_amount.append("Normal");
    c_amount.append("Extra");
    c_amount.append("Drenched");

    b_amount.pack_start(c_amount, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_amount, Gtk::PACK_SHRINK);  
    // Show dialog
    dialog->add_button("Cancel", 0);
    dialog->add_button("Complete Serving ", 1);
    dialog->add_button("Go to Scoop", 2);
    dialog->add_button("Add Topping", 3);
    dialog->add_button("Serving Info", 4);
    dialog->add_button("Show Image", 5);

    dialog->show_all();
    int result = dialog->run();

    dialog->close();
    while (Gtk::Main::events_pending())  Gtk::Main::iteration();   

    int scoop_amount = serving.get_number_scoops();
    int scoop_limit = serving.get_container().get_scoop_limit();

    if (c_top.get_active_row_number() == -1 && (result ==5 || result == 3 )) throw runtime_error ("Need to select a top first"); 

    if (result == 2){//go to scoop
       create_scoop_for_serving (order_ptr,serving,scoop_amount,scoop_limit);
    }
    else if (result==3){//Add topping
       int index_top = c_top.get_active_row_number();
       Topping* top =  dynamic_cast<Topping*>(tops[index_top]);
       int index_amount = c_amount.get_active_row_number();
       top->set_amount(index_amount+1);
       serving.add_top(*top);
       create_topping_for_serving(order_ptr,serving);
    }
    else if (result==1){
       //Need to Add serving to order
       //Need to add : add serving to order
       int answer= question("Do you want to add more serving in order?","Question",{"Yes","No"});
       if (answer == 0 ){ //add serving to order then show dialogs again
         order_ptr->add_serving(serving);
         show_create_serving_dialog(order_ptr);
         
       }
       else if (answer == 1){ //add serving then add order to emporium
         order_ptr->add_serving(serving);
         emporium.add_order(order_ptr);       
       }
    }
    else if (result==4){
       show_serving_info (serving);
       create_scoop_for_serving (order_ptr, serving,scoop_amount,scoop_limit);
    }
    else if (result == 5){
       int index = c_top.get_active_row_number();
       std::string image_name = tops[index]->get_image_name();
       Gtk::Image image(image_name);
       create_image_dialog("Image",image);
       create_topping_for_serving(order_ptr,serving);
    }
}

//Show info for Serving
void View::show_serving_info (Serving& serving){
   create_message_dialog("Serving Info", serving.to_string_serving());
}



void View::create_chosen_type_dialog(std::string type_name){
    Gtk::Dialog dialog;
    dialog.set_title("Create "+type_name);

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
    dialog.get_vbox()->pack_start(b_name, Gtk::PACK_SHRINK);
    
    //Description
    Gtk::HBox b_description;

    Gtk::Label l_description{"Description:"};
    l_description.set_width_chars(15);
    b_description.pack_start(l_description, Gtk::PACK_SHRINK);

    Gtk::Entry e_description;
    e_description.set_max_length(50);
    b_description.pack_start(e_description, Gtk::PACK_SHRINK);
    dialog.get_vbox()->pack_start(b_description, Gtk::PACK_SHRINK);

    //Wholesale_cost
    Gtk::HBox b_wholesale_cost;

    Gtk::Label l_wholesale_cost{"Wholesale Cost:"};
    l_wholesale_cost.set_width_chars(15);
    b_wholesale_cost.pack_start(l_wholesale_cost, Gtk::PACK_SHRINK);

    Gtk::Entry e_wholesale_cost;
    e_wholesale_cost.set_max_length(50);
    b_wholesale_cost.pack_start(e_wholesale_cost, Gtk::PACK_SHRINK);
    dialog.get_vbox()->pack_start(b_wholesale_cost, Gtk::PACK_SHRINK);
  /*
    // Image Link
    Gtk::HBox b_retail_price;

    Gtk::Label l_retail_price{"Retail Price:"};
    l_retail_price.set_width_chars(15);
    b_retail_price.pack_start(l_retail_price, Gtk::PACK_SHRINK);

    Gtk::Entry e_retail_price;
    e_retail_price.set_max_length(50);
    b_retail_price.pack_start(e_retail_price, Gtk::PACK_SHRINK);
    dialog.get_vbox()->pack_start(b_retail_price, Gtk::PACK_SHRINK);
 */


    // Retail_price
    Gtk::HBox b_retail_price;

    Gtk::Label l_retail_price{"Retail Price:"};
    l_retail_price.set_width_chars(15);
    b_retail_price.pack_start(l_retail_price, Gtk::PACK_SHRINK);

    Gtk::Entry e_retail_price;
    e_retail_price.set_max_length(50);
    b_retail_price.pack_start(e_retail_price, Gtk::PACK_SHRINK);
    dialog.get_vbox()->pack_start(b_retail_price, Gtk::PACK_SHRINK);
    
    Gtk::Entry e_scoop_limit;
    Gtk::HBox b_scoop_limit;
    Gtk::Label l_scoop_limit{"Scoop Limit:"};
    if (type_name == "Container"){
     // Scoop limit

     l_scoop_limit.set_width_chars(15);
     b_scoop_limit.pack_start(l_scoop_limit, Gtk::PACK_SHRINK);

     e_scoop_limit.set_max_length(50);
     b_scoop_limit.pack_start(e_scoop_limit, Gtk::PACK_SHRINK);
     dialog.get_vbox()->pack_start(b_scoop_limit, Gtk::PACK_SHRINK);
  }
    // Show dialog
    dialog.add_button("Cancel", 0);
    dialog.add_button("OK", 1);
    dialog.show_all();

    while (Gtk::Main::events_pending())  Gtk::Main::iteration();
    bool valid_data=false;
    std::regex word{"(\\w+ ?)+"};

    while (!valid_data){
      if (dialog.run()!=1){
       dialog.close();
       //show_create_item_dialog();
       return ;
       }
       valid_data = true;
       try {
        wholesale_cost =  std::stod (e_wholesale_cost.get_text());
       }
      catch (std::exception e) {
        e_wholesale_cost.set_text("***Invalid Amount***");
        valid_data=false;  
      }
      try {
        retail_price = std::stod (e_retail_price.get_text());
      }
      catch (std::exception e) {
        e_retail_price.set_text("***Invalid Amount***");
        valid_data=false;  
      }
      if(type_name == "Container"){
        try {
          limit =std::stoi(e_scoop_limit.get_text().c_str());
        }
        catch (std::exception e) {
          e_scoop_limit.set_text("***Invalid Amount***");
          valid_data=false;  
        }
      }
      //R E G U L A R  E X P R E S S
      std::string name_str =e_name.get_text();
      if (std::regex_match (name_str,word)){
        name = e_name.get_text();
      }
      else {
        e_name.set_text("***Invalid Input***"); 
        valid_data=false; 
      }
      std::string description_str =e_description.get_text();
      if (std::regex_match (description_str,word)){
        description = e_description.get_text();
        description = e_description.get_text();
      }
      else {
        e_description.set_text("***Invalid Input***");
        valid_data=false; 
      }
    }
    //std::string image_link = e_image_link.get_text();
    if (type_name == "Container") emporium.add_container(new Container(name, description,wholesale_cost,retail_price,limit/*,image_link*/));
    else if (type_name == "Ice Cream Flavor")emporium.add_scoop(new Scoop(name, description,wholesale_cost,retail_price/*,image_link*/));
    else if (type_name == "Topping") emporium.add_top(new Topping(name, description,wholesale_cost,retail_price/*,image_link*/));
    dialog.close();
     // show_create_item_dialog(); 
         
}
/////////////////////
/////D I A L O G////
////////////////////
void View::create_message_dialog(std::string title, std::string msg) {
    Gtk::MessageDialog *dialog = new Gtk::MessageDialog(title);
    dialog->set_secondary_text(msg, true);
    dialog->run();

    dialog->close();
    while (Gtk::Main::events_pending())  Gtk::Main::iteration();

    delete dialog;
}
void View::create_image_dialog(std::string title,Gtk::Image& image) {
    Gtk::Dialog *dialog = new Gtk::Dialog();
    dialog->set_title(title);
    dialog->set_default_size (200,200) ;
    Gtk::HBox b_image;

    std::cout << "Adding Image" << std::endl;
    b_image.pack_start(image , Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_image, Gtk::PACK_SHRINK);  

    //Show all 
    dialog->add_button("OK", 1);
    dialog->show_all();
    dialog->run();
    dialog->close();
    while (Gtk::Main::events_pending())  Gtk::Main::iteration();

    delete dialog;

}
// A question is a message that allows the user to respond with a button
int View::question(std::string msg, std::string title, std::vector<std::string> buttons) {
    Gtk::Dialog *dialog = new Gtk::Dialog();
    dialog->set_title(title);

    Gtk::Label *label = new Gtk::Label(msg);
    label->set_use_markup(true);
    dialog->get_content_area()->pack_start(*label);
    label->show();

    for(int i=0; i<buttons.size(); ++i) dialog->add_button(buttons[i], i);

    int result = dialog->run();

    dialog->close();
    while (Gtk::Main::events_pending())  Gtk::Main::iteration();

    delete label;
    delete dialog;

    return result;
}
std::string View::input_dialog(std::string msg, std::string title) {
    Gtk::Dialog *dialog = new Gtk::Dialog();
    dialog->set_title(title);

    Gtk::HBox b;
    Gtk::Entry e;
    e.set_text(msg);
    e.set_max_length(50);
    b.pack_start(e, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b, Gtk::PACK_SHRINK);

    dialog->add_button("Cancel", 0);
    dialog->add_button("OK", 1);
    dialog->show_all();

    int result = dialog->run();
    dialog->close();
    if (result == 1 ){
       return e.get_text();
    }
    else {
      return "none";
     }


}
int View::entry_amount_dialog(std::string msg, std::string title){
 Gtk::Dialog *dialog = new Gtk::Dialog();
    dialog->set_title(title);

    Gtk::Label *label = new Gtk::Label(msg);
    label->set_use_markup(true);
    dialog->get_content_area()->pack_start(*label);
    label->show();

    Gtk::HBox b_amount;

    Gtk::Entry e_amount;
    e_amount.set_max_length(50);
    b_amount.pack_start(e_amount, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_amount, Gtk::PACK_SHRINK);

    dialog->add_button("Cancel", 0);
    dialog->add_button("OK", 1);
    dialog->show_all();

    bool valid_data=false;
    int amount ;

    while (!valid_data){
      if (dialog->run()!=1){
         dialog -> close();
         return -1;
      }
      valid_data = true;
      try {
        amount = std::stoi(e_amount.get_text());
      }
      catch (std::exception e) {
        e_amount.set_text("*****Invalid Amount*****");
        valid_data=false;  
      }
      if (amount < 0 || amount > 25){
        e_amount.set_text("*****Amount Reach Limit*****");
        valid_data=false;  
      }
    }
  dialog->close();
  return amount;
}

std::string View::get_file_name() {return file_name;}
void View::set_file_name(std::string name) { file_name =name;}
//Emporium
