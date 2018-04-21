#include "controller.h"
#include <iostream>
#include <string>
#include "topping.h"
#include "scoop.h"
#include "container.h"

using namespace std;

void Controller::cli () {
  int cmd = -1;
  while (cmd != 0) {
    view.show_menu();
    cout << "Command? ";
    cin >> cmd;
    cin.ignore(); // consume \n
    execute_cmd(cmd);
  } 
}

void Controller::execute_cmd (int cmd){
 if (cmd == 1) { // Add scoop
    string name, description;
    double wholesale_cost,retail_price;
    int stock_remaining;

    cout << "Name? ";
    getline(cin, name);

    cout << "Description? ";
    getline(cin, description);

    cout << "Wholesale cost? ";
    cin>>wholesale_cost;
    cin.ignore();

    cout << "retail_price? ";
    cin>>retail_price;
    cin.ignore();

   // cout << "stock_remaining? ";
   // cin>>stock_remaining;
   // cin.ignore();

    emporium.add_scoop(new Scoop(name, description,wholesale_cost,retail_price));
}

 else if (cmd == 2) { // List all scoops
    view.list_scoops();
 }
 else if (cmd == 3) { // Add container
    string name, description;
    double wholesale_cost,retail_price;
    int stock_remaining;
    int scoop_limit;

    cout << "Name? ";
    getline(cin, name);

    cout << "Description? ";
    getline(cin, description);

    cout << "Wholesale cost? ";
    cin>>wholesale_cost;
    cin.ignore();

    cout << "retail_price? ";
    cin>>retail_price;
    cin.ignore();

   // cout << "stock_remaining? ";
   // cin>>stock_remaining;
   // cin.ignore();

    cout << "scoop_limit? ";
    cin>>scoop_limit;
    cin.ignore();


    emporium.add_container(new Container(name, description,wholesale_cost,retail_price,scoop_limit));
}

 else if (cmd == 4) { // List all containers
    view.list_containers();
 }
 else if (cmd == 5) { // Add topping
    string name, description;
    double wholesale_cost,retail_price;
    int amount;

    cout << "Name? ";
    getline(cin, name);

    cout << "Description? ";
    getline(cin, description);

    cout << "Wholesale cost? ";
    cin>>wholesale_cost;
    cin.ignore();

    cout << "retail_price? ";
    cin>>retail_price;
    cin.ignore();

    cout << "amount? ";
    cin>>amount;
    cin.ignore();


   // cout << "stock_remaining? ";
   // cin>>stock_remaining;
   // cin.ignore();

    emporium.add_top(new Topping(name, description,wholesale_cost,retail_price,amount));
}

 else if (cmd == 6) { // List all toppings
    view.list_toppings();
 }
 else if (cmd==7){ // Add item in dialogs
    view.show_create_item_dialog();
}
 else if (cmd==8){ // Create serving in dialogs
    order_id+=1;
    Order* order_ptr = new Order(order_id, *person_ptr); 
    view.show_create_serving_dialog( order_ptr);
}
 else if (cmd==9){ // Restock items
    int item_index = view.show_items();
    if(item_index == -1) return;
    int amount = view.entry_amount_dialog("Amount?","How many do you want to restock?");
    std::cout << "Item_index: "<<item_index << std::endl
              << "Amount " << amount << std::endl;
    emporium.restock_item(item_index,amount);
}
 else if (cmd==10){ // Fill Order
    int order_index = view.show_unfilled_orders();
    if(order_index == -1) return;
    emporium.fill_order(order_index,dynamic_cast<Server*>(person_ptr));
}

 else if (cmd==99) {//Test
    emporium.auto_add();
}
}
//GET FUnCTIONS
Emporium& Controller::get_emporium () {return emporium;} 

//Set Function
void Controller::set_person ( Person* per) {person_ptr =per;}


