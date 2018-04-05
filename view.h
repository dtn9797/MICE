#ifndef VIEW_H
#define VIEW_H

#include "emporium.h"

class View {
  private:
    Emporium& emporium;
  public:
   View (Emporium& emp): emporium{emp} {}
   void show_menu ();
   void list_scoops ();
   void list_containers();
   void list_toppings();
};

#endif
