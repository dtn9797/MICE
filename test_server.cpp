#include "test_server.h"
#include <iostream>
#include "server.h"
#include <fstream>
bool test_server () {
  std::string expected = "";
  bool passed = true; // Optimist!

  //
  // Test constructor
  //

  std::string x_name = "Duy Nguyen";
  int x_id =12345;
  double x_hour_salary = 10;

  Server server (x_name,x_id,x_hour_salary);
//Test construction
  if (server.get_name() != x_name ||
      server.get_id() != x_id ||
      server.type() != "Server"||
      server.get_hour_salary() != 10) {
    std::cerr << "#### Server constructor fail" << std::endl;
    std::cerr << "Expected: " << x_name << ',' 
                              << x_id << ','
                              << "Server" << ','
                              << x_hour_salary << std::endl;
    std::cerr << "Actual:   " << server.get_name() << ',' 
                              << server.get_id() << ','
                              << server.type() << ','
                              << server.get_hour_salary()<< std::endl;
    passed = false;
  }

//Test increase order_filled
  server.add_order_filled();
  if (server.get_num_order_filled() != 1){
    std::cerr << "#### Sever add_order_filled fail" << std::endl;
    std::cerr << "Expected: " << '1' << std::endl;
    std::cerr << "Actual: " << server.get_num_order_filled()<<std::endl;
    passed = false;
  }

  //test files

  std::ofstream ofs ("test_server.cpt",std::ifstream::out);
  server.save(ofs);
  ofs.close();
  std::ifstream ifs ("test_server.cpt",std::ifstream::in);
  std::string header1,header2 ;
  Server server0;
  std::getline(ifs, header1); // header
  std::getline(ifs, header2);
  if (header1 != "#") throw std::runtime_error("No Server records in file");
  else if (header2 != "Server") throw std::runtime_error("Malformed Sever record");
  //std::cout << type << std::endl;
  else {server0 = Server(ifs);};

  std::ofstream ofs0 ("test_server_result.cpt",std::ifstream::out);
  server0.save(ofs0);
  return passed;
}
