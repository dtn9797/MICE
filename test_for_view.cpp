#include "view.h"
#include "emporium.h"
int main () {
  Emporium em;
  View view(em);
  em.auto_add();

  view.show_menu();
  std::cout << "-----------------"<<std::endl;
  view.list_scoops();
  std::cout << "-----------------"<<std::endl;
  view.list_containers();
  std::cout << "-----------------"<<std::endl;
  view.list_toppings();
}
