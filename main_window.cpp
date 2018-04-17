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
  row[m_Columns.m_col_name] = "Billy Bob";

  Gtk::TreeModel::Row childrow = *(m_refTreeModel->append(row.children()));
  childrow[m_Columns.m_col_id] = 11;
  childrow[m_Columns.m_col_name] = "sadsadddddddddddddddddddddsdaddddddddddddddddddddddwadwdwadaedasdwadasdwadsdwasdwasdwdaawdaBilly Bob Junior";

  childrow = *(m_refTreeModel->append(row.children()));
  childrow[m_Columns.m_col_id] = 12;
  childrow[m_Columns.m_col_name] = "Sue Bob";

  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 2;
  row[m_Columns.m_col_name] = "Joey Jojo";


  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 3;
  row[m_Columns.m_col_name] = "Rob McRoberts";

  childrow = *(m_refTreeModel->append(row.children()));
  childrow[m_Columns.m_col_id] = 31;
  childrow[m_Columns.m_col_name] = "Xavier McRoberts";

  //Add the TreeView's view columns:
  m_TreeView.append_column("ID", m_Columns.m_col_id);
  m_TreeView.append_column("Name", m_Columns.m_col_name);

  //Connect signal:
  m_TreeView.signal_row_activated().connect(sigc::mem_fun(*this,
              &Main_window::on_treeview_row_activated) );

  show_all_children();
}


void Main_window::on_treeview_row_activated(const Gtk::TreeModel::Path& path,
        Gtk::TreeViewColumn* /* column */)
{
  Gtk::TreeModel::iterator iter = m_refTreeModel->get_iter(path);
  if(iter)
  {
    Gtk::TreeModel::Row row = *iter;
    std::cout << "Row activated: ID=" << row[m_Columns.m_col_id] << ", Name="
        << row[m_Columns.m_col_name] << std::endl;
  }
}
///////////////////////
//WHO IS CONTROLLING?//
//////////////////////
void Main_window::show_window_for_person(){
    int person;

    Gtk::Dialog *dialog = new Gtk::Dialog();
    dialog->set_title("Switch Controller");
    // Add Person
    Gtk::HBox b_person;

    Gtk::Label l_person{"Person:"};
    l_person.set_width_chars(15);
    b_person.pack_start(l_person, Gtk::PACK_SHRINK);

    Gtk::ComboBoxText c_person;
    c_person.set_size_request(160);
    std::vector<Person*> persons = controller.get_emporium().get_persons();
    for (Person* person: persons){
      std::string person_info = person -> get_name () + "(Id: " ; //atoi(person -> get_id ()) +" )";
      c_person.append(person_info);
    }

    b_person.pack_start(c_person, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_person, Gtk::PACK_SHRINK);  
 
    // Show dialog
    dialog->add_button("Cancel", 0);
    dialog->add_button("Log in", 1);
    dialog->show_all();
    int result = dialog->run();

    dialog->close();
    while (Gtk::Main::events_pending())  Gtk::Main::iteration();   

    if (result == 1){
       int index  = c_person.get_active_row_number();
         if (persons[index] -> type() == "Owner"){
           show_window_for_owner(persons[index]);
           controller.set_person(*(persons[index]));
         }
         else if (persons[index]->type() == "Manager"){
           show_window_for_manager(persons[index]);
           controller.set_person(*(persons[index]));
         }
         else if (persons[index]->type() == "Server"){
           show_window_for_server(persons[index]);
           controller.set_person(*(persons[index]));
         }
         else if (persons[index]->type() == "Customer"){
           show_window_for_customer(persons[index]);
           controller.set_person(*(persons[index]));
         }
    }
 
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

void Main_window::create_toggletoolbuttons_with_toolbar (Person *person,Gtk::Box *vbox) {
   //B O T T O M  T O O L  B A R
  Gtk::Toolbar *bottomtoolbar = Gtk::manage(new Gtk::Toolbar);   
  vbox->add(*bottomtoolbar);
  //  SERVER
  Gtk::Image *server_button_image = Gtk::manage(new Gtk::Image("server.png"));
  server_button = Gtk::manage(new Gtk::ToggleToolButton(*server_button_image));
  server_button->set_tooltip_markup("Server");
  server_button->set_sensitive (false); 
  bottomtoolbar->append(*server_button);
  // CUSTOMER
  Gtk::Image *customer_button_image = Gtk::manage(new Gtk::Image("customer.png"));
  customer_button = Gtk::manage(new Gtk::ToggleToolButton(*customer_button_image));
  customer_button->set_tooltip_markup("Customer");
  customer_button->set_sensitive (false); 
  bottomtoolbar->append(*customer_button);
  // MANAGER
  Gtk::Image *manager_button_image = Gtk::manage(new Gtk::Image("manager.png"));
  manager_button = Gtk::manage(new Gtk::ToggleToolButton(*manager_button_image));
  manager_button->set_tooltip_markup("Manager");
  manager_button->set_sensitive (false); 
  bottomtoolbar->append(*manager_button); 
  // OWNER
  Gtk::Image *owner_button_image = Gtk::manage(new Gtk::Image("owner.png"));
  owner_button = Gtk::manage(new Gtk::ToggleToolButton(*owner_button_image));
  owner_button->set_tooltip_markup("Owner");
  owner_button->set_sensitive (false); 
  bottomtoolbar->append(*owner_button);
  // SWITCH PERSON 
  Gtk::Image *switch_person_button_image = Gtk::manage(new Gtk::Image("reload.png"));
  switch_person_button = Gtk::manage(new Gtk::ToolButton(*switch_person_button_image));
  switch_person_button->set_tooltip_markup("Switch to other person");
  switch_person_button->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_switch_person_click));  
  bottomtoolbar->append(*switch_person_button);
  if (person->type () == "Owner"){
     owner_button->set_active(true);
}
  else if (person->type () == "Manager"){
     manager_button->set_active(true);
}
  else if (person->type () == "Server"){
     server_button->set_active(true);
}
  else if (person->type () == "Customer"){
     customer_button->set_active(true);
}

};
////////////////////
///Private FUnctions for Person//
///////////////////////
void Main_window::show_window_for_owner(Person* person) {
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
  //////////////
  //B O T T O M  T O O L  B A R
  create_toggletoolbuttons_with_toolbar ( person,vbox); 
   
  //SHOW ALL ITEMS
  vbox->show_all();
}

void Main_window::show_window_for_manager(Person* person) {
  //
  //MANAGER 
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
  std::vector<std::string> sub_names= {"_Test","_Properties","_Quit"};
  //     FILE
  create_menu_items(menubar,"_File", sub_names);
  //SUBMENUS FOR EDIT
  sub_names= {"_Undo","_Customer","_Server","_Item"};
  //     EDIT
  create_menu_items(menubar,"_Edit", sub_names);
  //         Quit for file
  //SUBMENUS FOR CREATE
  sub_names= {"_Order","_Customer","_Item","_Server"};
  //    CREATE
  create_menu_items(menubar,"_Create", sub_names);
  //SUBMENUS FOR PROCESS
  sub_names= {"_Cancel Order"};
  //    PROCESS
  create_menu_items(menubar,"_Process", sub_names);
  //SUBMENUS FOR REPORT
  sub_names = {"_Servers","_Customer","_Inventory","_Orders","_P&L"};
  //    REPORT
  create_menu_items(menubar,"_Report", sub_names);
  //SUBMENUS FOR ROLE
  sub_names= {"_Owner","_Manager", "_Server","_Customer"};
  //    ROLE
  create_menu_items(menubar,"_Role", sub_names);
  //SUBMENUS FOR HELP
  sub_names= {"_Manual","_About"};
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
  //////////////
  //B O T T O M  T O O L  B A R
  create_toggletoolbuttons_with_toolbar ( person,vbox); 

  //SHOW ALL ITEMS
  vbox->show_all();
}

void Main_window::show_window_for_server(Person* person) {
  //
  //SERVER
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
  std::vector<std::string> sub_names= {"_Properties"};
  //     FILE
  create_menu_items(menubar,"_File", sub_names);
  //SUBMENUS FOR EDIT
  sub_names= {"_Undo","_Restock","_Customer"};
  //     EDIT
  create_menu_items(menubar,"_Edit", sub_names);
  //         Quit for file
  // Append Quit to the File menu
 
  //SUBMENUS FOR CREATE
  sub_names= {"_Order","_Customer"};
  //    CREATE
  create_menu_items(menubar,"_Create", sub_names);

  //SUBMENUS FOR PROCESS
  sub_names= {"_Fill Order","_Payment", "_Cancel Order"};
  //    PROCESS
  create_menu_items(menubar,"_Process", sub_names);
  //SUBMENUS FOR ROLE
  sub_names= {"_Owner","_Manager", "_Server","_Customer"};
  //    ROLE
  create_menu_items(menubar,"_Role", sub_names);
  //SUBMENUS FOR HELP
  sub_names= {"_Manual","_About"};
  //    HELP
  create_menu_items(menubar,"_Help", sub_names);

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
  //////////////
  //B O T T O M  T O O L  B A R
  create_toggletoolbuttons_with_toolbar ( person,vbox); 

  //SHOW ALL ITEMS
  vbox->show_all();
}

void Main_window::show_window_for_customer(Person* person) {
  //
  //CUSTOMER
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
  std::vector<std::string> sub_names= {"_Properties"};
  //     FILE
  create_menu_items(menubar,"_File", sub_names);
  //SUBMENUS FOR EDIT
  sub_names= {"_Undo","_Restock","_Customer","_Server","_Manager","_Owner","_Item"};
  //     EDIT
  create_menu_items(menubar,"_Edit", sub_names);
  //SUBMENUS FOR CREATE
  sub_names= {"_Order","_Customer","_Item","_Server"};
  //    CREATE
  create_menu_items(menubar,"_Create", sub_names);

  //SUBMENUS FOR PROCESS
  sub_names= {"_Cancel Order"};
  //    PROCESS
  create_menu_items(menubar,"_Process", sub_names);
  //SUBMENUS FOR ROLE
  sub_names= {"_Owner","_Manager", "_Server","_Customer"};
  //    ROLE
  create_menu_items(menubar,"_Role", sub_names);
  //SUBMENUS FOR HELP
  sub_names= {"_About"};
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
  //////////////
  //B O T T O M  T O O L  B A R
  create_toggletoolbuttons_with_toolbar ( person,vbox); 
   


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
   std::cout<< " On _order_clicked\n"; 
   //create serving
   controller.execute_cmd(8);
}
void Main_window::on_create_item_click() {
    std::cout<< " On _item_clicked\n";
    controller.execute_cmd(7);
}
void Main_window::on_test_click() {
    std::cout<< " On _test_clicked\n";
    controller.execute_cmd(99);
}


///////////////////////////////
//D E S C O N S T R U T O R////
///////////////////////////////
void Main_window::on_switch_person_click() {
  remove ();
  show_window_for_person();
}


Main_window::~Main_window() { }
