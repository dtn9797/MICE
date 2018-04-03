#include "topping.h"
#include "scoop.h"
#include "container.h"

int main () {
  //test for topping class
   Topping top ("Light","It is very light",.25,.5,10,"Light"); 
  //test for scoop class
   Scoop scoop ("Vanilla","Favorite of Manager",.5,1,11,"Vanilla");
  //test for container class
   Container container("Bowls","General",.25,.5,10,"Bowls",5);

  
  return 0;
}
