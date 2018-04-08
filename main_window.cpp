#include "main_window.h"
#include <vector>

/////////////////////////
//C O N S T R U C T O R//
/////////////////////////
Main_window::Main_window (Controller& con): controller{con} {
  //
  //GUI SETUP
  //
  set_default_size (768,768);
  //Put verticalbox container
  Gtk::Box *vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
  add(*vbox);
  // //////////
  // M E N U B A R///
  // Add a menu bar as the top item in the vertical box
  Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar());
  vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);
  //SUBMENUS FOR FILE 
  std::vector<std::string> sub_names= {"_Properties","_Quit"};
  //     FILE
  create_menu_items(menubar,"_File", sub_names);

  //SUBMENUS FOR EDIT
  sub_names= {};
  //     EDIT
  create_menu_items(menubar,"_Edit", sub_names);
  //         Quit for file
  // Append Quit to the File menu
 
  //SUBMENUS FOR CREATE
  sub_names= {"_Order","_Item"};
  //    CREATE
  create_menu_items(menubar,"_Create", sub_names);

  //SUBMENUS FOR PROCESS
  sub_names= {};
  //    PROCESS
  create_menu_items(menubar,"_Process", sub_names);
  //    REPORT
  create_menu_items(menubar,"_Report", sub_names);
  //    ROLE
  create_menu_items(menubar,"_Role", sub_names);
  //    HELP
  create_menu_items(menubar,"_Help", sub_names);
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
							{"Properties", sigc::mem_fun(*this, &Main_window::on_properties_click)},
							{"Order", sigc::mem_fun(*this, &Main_window::on_order_click)},
							{"Item", sigc::mem_fun(*this, &Main_window::on_item_click)}
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

void Main_window::on_quit_click() {
    hide();
}
void Main_window::on_properties_click() {
    hide();
}
void Main_window::on_order_click() {
    hide();
}
void Main_window::on_item_click() {
    hide();
}

Main_window::~Main_window() { }
