#include "main_window.h"
#include <vector>

/////////////////////////
//C O N S T R U C T O R//
/////////////////////////
Main_window::Main_window (Controller& con): controller{con} {

  set_default_size (768,768);
  //Put verticalbox container
  vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
  add(*vbox);
  // //////////
  // M E N U B A R///
  // Add a menu bar as the top item in the vertical box
  Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar());
  vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);
  //SUBMENUS FOR FILE 
  std::vector<std::string> sub_names= {"_Test","_Quit"};
  //     FILE
  create_menu_items(menubar,"_File", sub_names);

    //SHOW ALL ITEMS
  vbox->show_all();
}



// ////////////////////////////////////////
// F U N C T I O N S  F O R  D E S I G N //
// ///////////////////////////////////////


void Main_window::create_menu_items(Gtk::MenuBar *menubar, std::string name, std::vector<std::string> sub_names){
 Gtk::MenuItem *menuitem_name = Gtk::manage(new Gtk::MenuItem(name, true));
  menubar->append(*menuitem_name);
  Gtk::Menu *namemenu = Gtk::manage(new Gtk::Menu());
  menuitem_name->set_submenu(*namemenu);
  //create_submenu_items
  std::map<std::string,sigc::slot<void>> str_to_func = {{"_Quit", sigc::mem_fun(*this, &Main_window::on_quit_click)},
							{"_Test", sigc::mem_fun(*this, &Main_window::on_test_click)}
							};
  for(std::string sub_name:sub_names) create_submenu_items(namemenu ,sub_name,str_to_func[sub_name]);
}

void Main_window::create_submenu_items(Gtk::Menu *namemenu,std::string name,sigc::slot<void> s){
 Gtk::MenuItem *menuitem_name = Gtk::manage(new Gtk::MenuItem(name, true));
  menuitem_name->signal_activate().connect(s);
  namemenu->append(*menuitem_name);
}



////////////////////////
/////C A L L  B A C K s//
///////////////////////


void Main_window::on_test_click() {
    int index = controller.get_emporium().number_of_orders();
    std::cout<< " On _test_clicked\n";
    //auto add order
    controller.execute_cmd(99);
     //BUG
    std::vector<std::string> record = controller.order_to_strings(0);
}

void Main_window::on_quit_click() {
   hide();
}

///////////////////////////////
//D E S C O N S T R U T O R////
///////////////////////////////

Main_window::~Main_window() { }
