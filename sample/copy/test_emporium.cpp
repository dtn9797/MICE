#include "emporium.h"
#include "scoop.h"
#include "test_emporium.h"
bool test_emporium () {
  Emporium em;
  em.auto_add();

  int size = em.number_of_scoop();
  for (int i =0 ; i<size; i++ ) std::cout<<em.scoop_to_string(i) <<std::endl;
  size = em.number_of_container();
  for (int i =0 ; i<size; i++ ) std::cout<<em.container_to_string(i) <<std::endl;
  size = em.number_of_scoop();
  for (int i =0 ; i<size; i++ ) std::cout<< em.top_to_string(i) << std::endl;

  return true;
}
