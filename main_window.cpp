#include "main_window.h"
#include <vector>

/////////////////////////
//C O N S T R U C T O R//
/////////////////////////
Main_window::Main_window (Controller& con): controller{con} {
  show_window_for_person();
  //Add the TreeView, inside a ScrolledWindow, with the button underneath:
  m_ScrolledWindow.add(m_TreeView);

  //Only show the scrollbars when they are necessary:
  m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

  vbox->pack_start(m_ScrolledWindow);
  //vbox->pack_start(m_ButtonBox, Gtk::PACK_SHRINK);

  //Create the Tree model:
  m_refTreeModel = Gtk::TreeStore::create(m_Columns);
  m_TreeView.set_model(m_refTreeModel);

  //All the items to be reordered with drag-and-drop:
  m_TreeView.set_reorderable();

  //Fill the TreeView's model
  Gtk::TreeModel::Row row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 1;
  row[m_Columns.m_col_server] = "Server";
  row[m_Columns.m_col_customer] = "Customer";
  row[m_Columns.m_col_state] = "State";
  row[m_Columns.m_col_price] = "10";

  Gtk::TreeModel::Row childrow = *(m_refTreeModel->append(row.children()));
  childrow[m_Columns.m_col_id] = 1;
  childrow[m_Columns.m_col_server] = "Serving Info :\n \tContainer:\n\t Box \n \tScoops: ....";


  row[m_Columns.m_col_id] = 1;
  row[m_Columns.m_col_server] = "Server";
  row[m_Columns.m_col_customer] = "Customer";
  row[m_Columns.m_col_state] = "State";
  row[m_Columns.m_col_price] = "10";



  //Add the TreeView's view columns:
  m_TreeView.append_column("ID", m_Columns.m_col_id);
  m_TreeView.append_column("Server", m_Columns.m_col_server);
  m_TreeView.append_column("Customer", m_Columns.m_col_customer);
  m_TreeView.append_column("State", m_Columns.m_col_state);
  m_TreeView.append_column("Price", m_Columns.m_col_price);

  /*
  //Connect signal:
  m_TreeView.signal_row_activated().connect(sigc::mem_fun(*this,
              &Main_window::on_treeview_row_activated) );
  */

  show_all_children();
}



///////////////////////
//WHO IS CONTROLLING?//
//////////////////////
void Main_window::show_window_for_person(){
  
show_window_for_owner();

 
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
							{"_Properties", sigc::mem_fun(*this, &Main_window::on_properties_click)},
							{"_Order", sigc::mem_fun(*this, &Main_window::on_create_order_click)},
							{"_Item", sigc::mem_fun(*this, &Main_window::on_create_item_click)},
							{"_Test", sigc::mem_fun(*this, &Main_window::on_test_click)}
							};
  for(std::string sub_name:sub_names) create_submenu_items(namemenu ,sub_name,str_to_func[sub_name]);
}

void Main_window::create_submenu_items(Gtk::Menu *namemenu,std::string name,sigc::slot<void> s){
 Gtk::MenuItem *menuitem_name = Gtk::manage(new Gtk::MenuItem(name, true));
  menuitem_name->signal_activate().connect(s);
  namemenu->append(*menuitem_name);
}


////////////////////
///Private FUnctions for Person//
///////////////////////
void Main_window::show_window_for_owner() {
  //
  //OWNER
  //
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
  std::vector<std::string> sub_names= {"_New","_Open","_Save","_Save As","_Properties","_Test","_Quit"};
  //     FILE
  create_menu_items(menubar,"_File", sub_names);

  //SUBMENUS FOR EDIT
  sub_names= {"_Undo","_Customer","_Server","_Manager","_Owner"};
  //     EDIT
  create_menu_items(menubar,"_Edit", sub_names);
  //         Quit for file
  // Append Quit to the File menu
 
  //SUBMENUS FOR CREATE
  sub_names= {"_Order","_Customer","_Item","_Server"};
  //    CREATE
  create_menu_items(menubar,"_Create", sub_names);
  //SUBMENUS FOR REPORT
  sub_names = {"_Servers","_Customer","_Inventory","_Orders","_P&L"};
  //    REPORT
  create_menu_items(menubar,"_Report", sub_names);
  //SUBMENUS FOR ROLE
  sub_names= {"_Owner","_Manager", "_Server","_Customer"};
  //    ROLE
  create_menu_items(menubar,"_Role", sub_names);
  //    HELP
  create_menu_items(menubar,"_Help", sub_names);

 // /////////////
  //T O P  T O O L B A R
  // Add a toolbar to the vertical box below the menu
  Gtk::Toolbar *toptoolbar = Gtk::manage(new Gtk::Toolbar);   
  vbox->add(*toptoolbar);
  //     N E W   E M P O R I UM
  // Add a new emporium icon
  Gtk::ToolButton *new_emporium_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::NEW));
  new_emporium_button->set_tooltip_markup("Create a New Emporium");
  //new_emporium_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_new_emporium_click));
  toptoolbar->append(*new_emporium_button);

  //     Q U I T
  // Add a icon for quitting
  Gtk::ToolButton *quit_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::QUIT));
  quit_button->set_tooltip_markup("Exit MICE");
  quit_button->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_quit_click));
  Gtk::SeparatorToolItem *sep = Gtk::manage(new Gtk::SeparatorToolItem());
  sep->set_expand(true);  // The expanding sep forces the Quit button to the right
  toptoolbar->append(*sep);
  toptoolbar->append(*quit_button); 
   
  //SHOW ALL ITEMS
  vbox->show_all();
}




////////////////////////
/////C A L L  B A C K s//
///////////////////////

void Main_window::on_quit_click() {
    std::cout<< " On _quit_clicked\n";
    hide();
}
void Main_window::on_properties_click() {

    std::cout<< " On _properties_clicked\n";
}
void Main_window::on_create_order_click() {
   //create serving
   controller.execute_cmd(8);

  
}
void Main_window::on_create_item_click() {
    std::cout<< " On _item_clicked\n";
    controller.execute_cmd(7);
}
void Main_window::on_test_click() {
    int index = controller.get_emporium().number_of_orders();
    std::cout<< " On _test_clicked\n";
    controller.execute_cmd(99);
    for (int i = index ; i< controller.get_emporium().number_of_orders();i++) add_row(i);
}
void Main_window::on_switch_person_click() {
  remove ();
  show_window_for_person();
}

///////////////////////////////
//D E S C O N S T R U T O R////
///////////////////////////////

Main_window::~Main_window() { }
