#include "test_order.h"
#include "customer.h"
#include "server.h"
#include "serving.h"
#include "order.h"
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
  //
  // Test for add order
  // 


 
   return passed;
}
