#include "controller.h"
#include <iostream>
#include <string>


using namespace std;


void Controller::execute_cmd (int cmd){

  if (cmd==99) {//Test
    emporium.auto_add();
}
}
//GET FUnCTIONS
Emporium& Controller::get_emporium () {return emporium;} 

//To String 
std::vector<std::string> Controller::order_to_strings(int index) {
   emporium.order_to_strings(index);
}

