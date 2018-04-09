#ifndef VIEW_H
#define VIEW_H

#include "emporium.h"
#include <gtkmm.h>
#include <string>

class View {
  private:
    Emporium& emporium;
    void create_chosen_type_dialog(std::string type_name);
  public:
   View (Emporium& emp): emporium{emp} {}
   void show_menu ();
   void list_scoops ();
   void list_containers();
   void list_toppings();
   //GUI
   void show_create_item_dialog();
};

#endif
