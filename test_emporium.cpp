#include "emporium.h"
#include "scoop.h"
#include "test_emporium.h"
bool test_emporium () {
  Emporium em;
  em.auto_add();
  int size = em.number_of_items();
  size = em.number_of_scoops();
  for (int i =0 ; i<size; i++ ) std::cout<<em.scoop_to_string(i) <<std::endl;
  size = em.number_of_containers();
  for (int i =0 ; i<size; i++ ) std::cout<<em.container_to_string(i) <<std::endl;
  size = em.number_of_toppings();
  for (int i =0 ; i<size; i++ ) std::cout<< em.topping_to_string(i) << std::endl;

  return true;
}
