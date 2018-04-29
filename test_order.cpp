#include "test_order.h"
#include "customer.h"
#include "server.h"
#include "serving.h"
#include "order.h"
#include <fstream>
bool test_order () {
  bool passed = true;
  //
  //Test for constructor
  //
  
    //Order (int id, Server sers): id_number{id} ,server{sers}{}
    //Order (int id, Customer cus): id_number{id} ,customer{cus}{}
   // Order (int id,Server ser, std::vector<Serving> sers): id_number{id}, server{ser} ,servings{sers} {}
    //Order (int id,Customer cus, std::vector<Serving> sers): id_number{id},customer{cus}, servings{sers} {}
 
   int x_id = 1;
   Customer x_cus ("C",2,"999");
   Server x_ser ("S",3,7.25);
   Order order0 (x_id,x_cus);
   Order order1 (x_id,x_ser);

   if (order0.get_id_number() != x_id || 
       order1.get_id_number() != x_id ||
       order0.get_customer().get_name() != "C" ||
       order1.get_server().get_name() != "S" ){
     std::cerr << "#Order Constructor Error";
     passed = false;
   }

  std::vector<Scoop> scoops = {Scoop ("Vanilla","General",1,1),Scoop ("Cookies", "Sweet",1,1)};
  std::vector<Topping> tops = {Topping("Whipped Cream","General",1,1,1), Topping("Chocolate Sauce", "Sweet",1,1,1) };
  Serving serving0 ( Container ("Cup","General",1,1,1), scoops, tops );
       
  //add order 
  order1.add_serving(serving0);     

  //test load/save
  std::string header1,header2;
  std::ofstream ofs{"test_order.cpt", std::ofstream::out};
  order1.save(ofs);
  ofs.close();
  std::ifstream ifs{"test_order.cpt", std::ofstream::in}; 
  std::getline(ifs, header1);
  std::getline(ifs, header2);
  if (header1 != "#") throw std::runtime_error("missing # during Order input ");
  if (header2 != "ORDER") throw std::runtime_error("missing ORDER during Order input ");
  order0 = Order(ifs); 
 //order result
  std::ofstream ofs0{"test_order_result.cpt", std::ofstream::out};
  order0.save(ofs0);
  ofs0.close();

 
   return passed;
}
