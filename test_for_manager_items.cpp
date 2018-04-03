#include "manager.h"
#include "items.h"
#include <iostream>
int main () {
  Items ite;
  Manager manager ("Duy",123,100,ite);
  manager.create_scoop();
  return 0; 
}
