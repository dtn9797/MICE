#include "emporium.h"
#include "scoop.h"
#include "test_emporium.h"
#include <vector>
#include <iostream>
#include <fstream>

bool test_emporium () {
  Emporium em;
  //auto add items
  em.auto_add();
  //need to write test for emporium
  std::string expected = "";
  bool passed = true; // Optimist!
  //
  // Test constructor
  //
  // if (em.serving)
  //ofstream ofs {"untitle.cpt",std::ofstream::out};
  std::string header1,header2;
  std::ofstream ofs{"test_emporium.cpt", std::ofstream::out};
  em.save(ofs);
  ofs.close();
  std::ifstream ifs{"test_emporium.cpt", std::ofstream::in}; 
  Emporium em0;
  std::getline(ifs,header1);
  std::getline(ifs,header2);
  if (header1 != "MICE") throw std::runtime_error("NOT an Emporium file");
  else if (header2 != "0.1") throw std::runtime_error("Incompatible file version");
  else {  em0.load(ifs); }
  //test
  std::ofstream ofs_result{"test_emporium_result.cpt", std::ofstream::out};
  em0.save(ofs_result);
  ofs.close();

  return true;
}
