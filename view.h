#ifndef VIEW_H
#define VIEW_H

#include "emporium.h"
#include "serving.h"
#include <gtkmm.h>
#include <string>

class View {
  private:
    Emporium& emporium;
    //create fresh one for emporium
    void create_chosen_type_dialog(std::string type_name);
    // serving
    void create_scoop_for_serving (Order* order_ptr,Serving& serving,int scoop_amount,int scoop_limit);
    void create_topping_for_serving (Order* order_ptr,Serving& serving);
    void show_serving_info (Serving& serving);
    //dialog
    int question(std::string msg, std::string title,
             std::vector<std::string> buttons);
    void create_image_dialog ( std::string title, Gtk::Image& image);
    std::string file_name = "untitle.cpt";
  public:
   View (Emporium& emp): emporium{emp} {}
   void show_menu ();
   void list_scoops ();
   void list_containers();
   void list_toppings();
   //GUI
   void show_create_item_dialog();
   void show_create_serving_dialog(Order* order_ptr);
   int show_items();
   int show_unfilled_orders();
   int show_filled_orders();
   int show_unfilled_orders_for_customer(Person *person_ptr);
   //dialog
   std::string input_dialog(std::string msg, std::string title);
   int entry_amount_dialog(std::string title, std::string msg);
   void create_message_dialog(std::string title, std::string msg);  
   std::string get_file_name(); 
   void set_file_name(std::string name);
};

#endif
