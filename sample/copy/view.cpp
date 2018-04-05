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
  for (int i=0; i<emporium.number_of_scoop(); ++i) {
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
  for (int i=0; i<emporium.number_of_container(); ++i) {
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
  for (int i=0; i<emporium.number_of_top(); ++i) {
    cout << i << ") " << emporium.top_to_string(i) << endl;
  }
}
