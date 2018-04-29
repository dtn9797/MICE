#include "test_serving.h"
#include "serving.h"
#include <iostream>
#include <vector>
#include <fstream>


bool test_serving () {
  std::string expected = "";
  bool passed = true; // Optimist!

  //
  // Test constructor
  //

    Container x_container("xContainer","xThis is a container",1,2,3);
    std::vector<Scoop> x_scoops={Scoop("xScoop","xThis is the first scoop",1,2),Scoop("xScoop","xThis is the second scoop",1,2)};
    std::vector<Topping> x_toppings={Topping("xToppings","xThese are scoops",1,2,1)};
    double x_wholesale_cost = x_container.get_wholesale_cost()+x_scoops[0].get_wholesale_cost()+x_scoops[1].get_wholesale_cost()+x_toppings[0].get_wholesale_cost();
    double x_retail_price = x_container.get_retail_price()+x_scoops[0].get_retail_price()+x_scoops[1].get_retail_price()+x_toppings[0].get_retail_price();

    Serving serving{x_container,x_scoops,x_toppings};

  if (serving.get_container().get_description() != x_container.get_description() ||
      serving.get_scoop(0).get_description() != x_scoops[0].get_description() ||
      serving.get_topping(0).get_description() != x_toppings[0].get_description() ||
      serving.get_wholesale_cost() != 4 ||
      serving.get_retail_price() !=  8) {
    std::cerr << "#### Serving constructor fail" << std::endl;
   
    std::cerr << "Expected: " << x_container.get_description()<< ','
                              << x_scoops[0].get_description()  << ','
                              << x_toppings[0].get_description() << ','
                              << '4' << ','
                              << '8' << ',' << std::endl;
    std::cerr << "Actual:   " << serving.get_container().get_description() << ','
                              << serving.get_scoop(0).get_description() << ','
                              << serving.get_topping(0).get_description()<< ','
                              << serving.get_wholesale_cost() << ','
                              << serving.get_retail_price() << std::endl;
   
    passed = false;
  }

  //
  //Check for out put
  //
  /*std::cout << "#####Check for cout from serving"<< std::endl
  << serving.to_string_serving() << std::endl;
  */
  //
  // Report results
  //

  //test load/save
  std::string header1,header2;

  std::ofstream ofs{"test_serving.cpt", std::ofstream::out};
  serving.save(ofs);
  ofs.close();
  std::ifstream ifs{"test_serving.cpt", std::ofstream::in}; 

  Container y_container("yContainer","yThis is a container",2,3,4);
  std::vector<Scoop> y_scoops={Scoop("yScoop","yThis is the first scoop",2,3),Scoop("yScoop","yThis is the second scoop",1,2)};
  std::vector<Topping> y_toppings={Topping("yToppings","yThese are scoops",2,3,2)};
  double y_wholesale_cost = y_container.get_wholesale_cost()+y_scoops[0].get_wholesale_cost()+y_scoops[1].get_wholesale_cost()+y_toppings[0].get_wholesale_cost();
  double y_retail_price = y_container.get_retail_price()+y_scoops[0].get_retail_price()+y_scoops[1].get_retail_price()+y_toppings[0].get_retail_price();

  Serving serving0{y_container,y_scoops,y_toppings};
  std::getline(ifs, header1); // header
  std::getline(ifs, header2);
  if (header1 != "#") throw std::runtime_error("No Serving records in file");
  else if (header2 != "SERVING") throw std::runtime_error("Malformed Serving record");
  else {serving0 = Serving(ifs);};
 //serving result
  std::ofstream ofs0{"test_serving_result.cpt", std::ofstream::out};
  serving0.save(ofs0);
  ofs0.close();
/*
  if (serving0.get_container().get_description() != x_container.get_description() ||
      serving0.get_scoop(0).get_description() != x_scoops[0].get_description() ||
      serving0.get_topping(0).get_description() != x_toppings[0].get_description() ||
      serving0.get_wholesale_cost() != 4 ||
      serving0.get_retail_price() !=  8) {
    std::cerr << "#### Serving constructor fail" << std::endl;
   
    std::cerr << "Expected: " << x_container.get_description()<< ','
                              << x_scoops[0].get_description()  << ','
                              << x_toppings[0].get_description() << ','
                              << '4' << ','
                              << '8' << ',' << std::endl;
    std::cerr << "Actual:   " << serving0.get_container().get_description() << ','
                              << serving0.get_scoop(0).get_description() << ','
                              << serving0.get_topping(0).get_description()<< ','
                              << serving0.get_wholesale_cost() << ','
                              << serving0.get_retail_price() << std::endl;
   
    passed = false;
  }
*/
  return passed;
} 
