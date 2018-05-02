#include "main_window.h"
#include <vector>
#include <fstream>

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
  //SUBMENUS FOR PROCESS
  sub_names= {"_Cancel Order","_Fill Order","_Payment", "_Restock"};
  //    PROCESS
  create_menu_items(menubar,"_Process", sub_names);
  //SUBMENUS FOR REPORT
  sub_names = {"_Servers","_Customer","_Inventory","_Orders","_P&L"};
  //    REPORT
  create_menu_items(menubar,"_Report", sub_names);
/*
  //SUBMENUS FOR ROLE
  sub_names= {"_Owner","_Manager", "_Server","_Customer"};
  //    ROLE
  create_menu_items(menubar,"_Role", sub_names);
*/
  //    HELP
  create_menu_items(menubar,"_Help", sub_names);

 // /////////////
  //T O P  T O O L B A R
  // Add a toolbar to the vertical box below the menu
  Gtk::Toolbar *toptoolbar = Gtk::manage(new Gtk::Toolbar);   
  vbox->add(*toptoolbar);
  //A D D  O R D E R  
  Gtk::Image *order_button_image = Gtk::manage(new Gtk::Image("add_order.png"));
  order_button = Gtk::manage(new Gtk::ToolButton(*order_button_image));
  order_button->set_tooltip_markup("Create New Order");
  order_button->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_create_order_click));   
  toptoolbar->append(*order_button); 
  //Fill  O R D E R  
  Gtk::Image *fill_button_image = Gtk::manage(new Gtk::Image("fill_order.png"));
  fill_button = Gtk::manage(new Gtk::ToolButton(*fill_button_image));
  fill_button->set_tooltip_markup("Fill Order");
  fill_button->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_filled_click));   
  toptoolbar->append(*fill_button);
  //P A Y M E N T
  Gtk::Image *payment_button_image = Gtk::manage(new Gtk::Image("pay.png"));
  payment_button = Gtk::manage(new Gtk::ToolButton(*payment_button_image));
  payment_button->set_tooltip_markup("Pay Order");
  payment_button->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_pay_click));    
  toptoolbar->append(*payment_button);
   //Cancel  O R D E R  
  Gtk::Image *cancel_button_image = Gtk::manage(new Gtk::Image("cancel_order.png"));
  cancel_button = Gtk::manage(new Gtk::ToolButton(*cancel_button_image));
  cancel_button->set_tooltip_markup("Cancel Order");
  cancel_button->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_cancel_click));  
  toptoolbar->append(*cancel_button); 
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
  create_toggletoolbuttons_with_toolbar ( controller.get_person_ptr(),vbox); 
  
  ///////////////
  //T R E E V I E W
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


  //Add the TreeView's view columns:
  m_TreeView.append_column("ID", m_Columns.m_col_id);
  m_TreeView.append_column("Server", m_Columns.m_col_server);
  m_TreeView.append_column("Customer", m_Columns.m_col_customer);
  m_TreeView.append_column("State", m_Columns.m_col_state);
  m_TreeView.append_column("Price", m_Columns.m_col_price);

  show_all_children();
   
  //SHOW ALL ITEMS
  vbox->show_all();
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
      std::string person_info = person -> type () + " : " + person -> get_name () + "(Id: " + std::to_string(person -> get_id ()) +" )";
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
         }
         else if (persons[index]->type() == "Manager"){
           show_window_for_manager(persons[index]);
         }
         else if (persons[index]->type() == "Server"){
           show_window_for_server(persons[index]);
         }
         else if (persons[index]->type() == "Customer"){
           show_window_for_customer(persons[index]);
         }
    }
    else if (result == 0 ){
        Person* person = controller.get_person_ptr();
          if (person -> type() == "Owner"){
           show_window_for_owner(person);
         }
         else if (person->type() == "Manager"){
           show_window_for_manager(person);
         }
         else if (person->type() == "Server"){
           show_window_for_server(person);
         }
         else if (person->type() == "Customer"){
           show_window_for_customer(person);
         }
         else {
          hide();
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
							{"_Test", sigc::mem_fun(*this, &Main_window::on_test_click)},
							{"_Restock", sigc::mem_fun(*this, &Main_window::on_restock_click)},
							{"_Fill Order", sigc::mem_fun(*this, &Main_window::on_filled_click)},
							{"_Cancel Order", sigc::mem_fun(*this, &Main_window::on_cancel_click)},
							{"_Payment", sigc::mem_fun(*this, &Main_window::on_pay_click)},
							{"_Save", sigc::mem_fun(*this, &Main_window::on_save_click)},
							{"_Open", sigc::mem_fun(*this, &Main_window::on_load_click)},
                                                        {"_Save As", sigc::mem_fun(*this, &Main_window::on_save_as_click)},
							};
  for(std::string sub_name:sub_names){
     create_submenu_items(namemenu ,sub_name,str_to_func[sub_name]);
  }
}

void Main_window::create_submenu_items(Gtk::Menu *namemenu,std::string name,sigc::slot<void> s){
 Gtk::MenuItem *menuitem_name = Gtk::manage(new Gtk::MenuItem(name, true));
  menuitem_name->signal_activate().connect(s);
  namemenu->append(*menuitem_name);

     if (name == "_New"){menuitem_new = menuitem_name;}
     else if (name =="_Open"){menuitem_open = menuitem_name;}
     else if (name =="_Save"){menuitem_save = menuitem_name;}
     else if (name =="_Test"){menuitem_test = menuitem_name;}
     else if (name =="_Quit"){menuitem_quit = menuitem_name;}
     else if (name =="_Order"){menuitem_order = menuitem_name;}
     else if (name =="_Customer"){menuitem_customer = menuitem_name;}
     else if (name =="_Item"){menuitem_item = menuitem_name;}
     else if (name =="_Server"){menuitem_server = menuitem_name;}
     else if (name =="_Fill Order"){menuitem_fill_order = menuitem_name;}
     else if (name =="_Payment"){menuitem_pay_for_order = menuitem_name;}
     else if (name =="_Cancel Order"){menuitem_cancel_order = menuitem_name;}
     else if (name =="_Restock"){menuitem_restock = menuitem_name;}
  
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
    menuitem_new->set_sensitive(true);
    menuitem_open->set_sensitive(true);
    menuitem_save->set_sensitive(true);
    menuitem_test->set_sensitive(true);
    menuitem_quit->set_sensitive(true);
    menuitem_order->set_sensitive(true);
    menuitem_customer->set_sensitive(true);
    menuitem_item->set_sensitive(true);
    menuitem_server->set_sensitive(true);
    menuitem_fill_order->set_sensitive(true);
    menuitem_pay_for_order->set_sensitive(true);
    menuitem_cancel_order->set_sensitive(true);
    menuitem_restock->set_sensitive(false);

    server_button->set_active(false);
    customer_button->set_active(false);
    manager_button->set_active(false);
    owner_button->set_active(true);

    order_button->set_sensitive(menuitem_order->get_sensitive());
    fill_button->set_sensitive(menuitem_fill_order->get_sensitive());
    payment_button->set_sensitive(menuitem_pay_for_order->get_sensitive());
    cancel_button->set_sensitive(menuitem_cancel_order->get_sensitive());

    controller.set_person(person);
}

void Main_window::show_window_for_manager(Person* person) {
    menuitem_new->set_sensitive(false);
    menuitem_open->set_sensitive(true);
    menuitem_save->set_sensitive(true);
    menuitem_test->set_sensitive(true);
    menuitem_quit->set_sensitive(true);
    menuitem_order->set_sensitive(true);
    menuitem_customer->set_sensitive(true);
    menuitem_item->set_sensitive(true);
    menuitem_server->set_sensitive(true);
    menuitem_fill_order->set_sensitive(true);
    menuitem_pay_for_order->set_sensitive(true);
    menuitem_cancel_order->set_sensitive(true);
    menuitem_restock->set_sensitive(false);

    order_button->set_sensitive(menuitem_order->get_sensitive());
    fill_button->set_sensitive(menuitem_fill_order->get_sensitive());
    payment_button->set_sensitive(menuitem_pay_for_order->get_sensitive());
    cancel_button->set_sensitive(menuitem_cancel_order->get_sensitive());

    server_button->set_active(false);
    customer_button->set_active(false);
    manager_button->set_active(true);
    owner_button->set_active(false);


    controller.set_person(person);
}

void Main_window::show_window_for_server(Person* person) {
    menuitem_new->set_sensitive(false);
    menuitem_open->set_sensitive(false);
    menuitem_save->set_sensitive(false);
    menuitem_test->set_sensitive(false);
    menuitem_quit->set_sensitive(true);
    menuitem_order->set_sensitive(true);
    menuitem_customer->set_sensitive(true);
    menuitem_item->set_sensitive(false);
    menuitem_server->set_sensitive(false);
    menuitem_fill_order->set_sensitive(true);
    menuitem_pay_for_order->set_sensitive(true);
    menuitem_cancel_order->set_sensitive(true);
    menuitem_restock->set_sensitive(true);

    order_button->set_sensitive(menuitem_order->get_sensitive());
    fill_button->set_sensitive(menuitem_fill_order->get_sensitive());
    payment_button->set_sensitive(menuitem_pay_for_order->get_sensitive());
    cancel_button->set_sensitive(menuitem_cancel_order->get_sensitive());

    server_button->set_active(true);
    customer_button->set_active(false);
    manager_button->set_active(false);
    owner_button->set_active(false);

    controller.set_person(person);

}

void Main_window::show_window_for_customer(Person* person) {
    menuitem_new->set_sensitive(false);
    menuitem_open->set_sensitive(false);
    menuitem_save->set_sensitive(false);
    menuitem_test->set_sensitive(false);
    menuitem_quit->set_sensitive(false);
    menuitem_order->set_sensitive(true);
    menuitem_customer->set_sensitive(false);
    menuitem_item->set_sensitive(false);
    menuitem_server->set_sensitive(false);
    menuitem_fill_order->set_sensitive(false);
    menuitem_pay_for_order->set_sensitive(false);
    menuitem_cancel_order->set_sensitive(true);
    menuitem_restock->set_sensitive(false);

    order_button->set_sensitive(menuitem_order->get_sensitive());
    fill_button->set_sensitive(menuitem_fill_order->get_sensitive());
    payment_button->set_sensitive(menuitem_pay_for_order->get_sensitive());
    cancel_button->set_sensitive(menuitem_cancel_order->get_sensitive());


    server_button->set_active(false);
    customer_button->set_active(true);
    manager_button->set_active(false);
    owner_button->set_active(false);

    controller.set_person(person);
}





////////////////////////
/////C A L L  B A C K s//
///////////////////////

void Main_window::on_quit_click() {
    std::cout<< " On _quit_clicked\n";
    hide();
}
void Main_window::on_properties_click() {
    delete_rows();
    std::cout<< " On _properties_clicked\n";
}
void Main_window::on_create_order_click() {
   //int index = controller.get_emporium().number_of_orders();
   //create serving
   controller.execute_cmd(8);
   //for (int i = index ; i< controller.get_emporium().number_of_orders();i++) add_row(i);
   delete_rows(); add_rows();
}
void Main_window::on_create_item_click() {
    std::cout<< " On _item_clicked\n";
    controller.execute_cmd(7);
}
void Main_window::on_test_click() {
    //int index = controller.get_emporium().number_of_orders();
    std::cout<< " On _test_clicked\n";
    controller.execute_cmd(99);  
    //for (int i = index ; i< controller.get_emporium().number_of_orders();i++) add_row(i);
    delete_rows(); add_rows();
}
void Main_window::on_switch_person_click() {
  //remove ();
  show_window_for_person();
  delete_rows();add_rows();
}
void Main_window::on_restock_click() {
  std::cout<< " On _restock_clicked" << std::endl;
  controller.execute_cmd(9);
}
void Main_window::on_filled_click() {
  std::cout<< " On _filled_clicked" << std::endl;
  controller.execute_cmd(10);
  //std::cout<< " Current filled num"<< dynamic_cast<Server*>(controller.get_emporium().get_persons()[2])->get_num_order_filled() << std::endl;
  update_rows();
}
void Main_window::on_cancel_click() {
  std::cout<< " On _cancel_clicked" << std::endl;
  controller.execute_cmd(11);
  update_rows();
}
void Main_window::on_pay_click() {
  std::cout<< " On _pay_clicked" << std::endl;
  controller.execute_cmd(12);
  update_rows();
}
void Main_window::on_save_click() {
  std::cout<< " On _save_clicked" << std::endl;
  controller.execute_cmd(13);
}
void Main_window::on_save_as_click() {
  std::cout<< " On _save_as_clicked" << std::endl;
  controller.execute_cmd(14);
}
void Main_window::on_load_click() {
  std::cout<< " On _load_clicked" << std::endl;
    Gtk::FileChooserDialog dialog("Please choose a file",
          Gtk::FileChooserAction::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);

    //Add response buttons the the dialog:
    dialog.add_button("_Cancel", 0);
    dialog.add_button("_Open", 1);

    int result = dialog.run();

    //Handle the response:
    if (result == 1) {
        std::ifstream ifs{dialog.get_filename(), std::ifstream::in};
        controller.get_emporium().load(ifs);
        delete_rows();
        for (int i = 0 ; i< controller.get_emporium().number_of_orders();i++) add_row(i);
        show_window_for_person();
    }

}

///////////////////////////////
//D E S C O N S T R U T O R////
///////////////////////////////

Main_window::~Main_window() { }

//////////////////////////
// U T I L I T I E S//////
//////////////////////////
void Main_window::update_rows() {
    Gtk::TreeIter iter = m_refTreeModel->get_iter("0");
    for(int i=0; i<controller.get_emporium().number_of_orders(); ++i) {
        //Update state
        int id = i;
        std::string server = controller.get_emporium().get_orders()[i]->get_server().get_name();
        std::string customer = controller.get_emporium().get_orders()[i]->get_customer().get_name();
        std::string state = controller.get_emporium().get_orders()[i]->get_state_string();
        std::string price = std::to_string(controller.get_emporium().get_orders()[i]->get_price());
        (*iter)[m_Columns.m_col_state] = state;
        (*iter)[m_Columns.m_col_id] = id;
        (*iter)[m_Columns.m_col_server] = server;
        (*iter)[m_Columns.m_col_customer] = customer;
        (*iter)[m_Columns.m_col_state] = state;
        (*iter)[m_Columns.m_col_price] = price;
        iter++;
    }
}
void Main_window::delete_rows(){
   // Gtk::TreeIter iter = m_refTreeModel->get_iter("0");
   /* for(int i=0; i<controller.get_emporium().number_of_orders()+1; ++i) {
       Gtk::TreeIter iter = m_refTreeModel->get_iter(std::to_string(i));
       m_refTreeModel->erase(iter);
    }*/
  m_refTreeModel->clear();
}
void Main_window:: add_row (int order_index) {


  Gtk::TreeModel::Row row = *(m_refTreeModel->append());
  // This line of code cause the error 
  //std::vector<std::string> record = controller.order_to_strings(order_index);
  int id = order_index;
  std::string server = controller.get_emporium().get_orders()[order_index]->get_server().get_name();
  std::string customer = controller.get_emporium().get_orders()[order_index]->get_customer().get_name();
  std::string state = controller.get_emporium().get_orders()[order_index]->get_state_string();
  std::string price = std::to_string(controller.get_emporium().get_orders()[order_index]->get_price());
  std::cout << "Price:" << price <<std::endl;

  row[m_Columns.m_col_id] = id;
  row[m_Columns.m_col_server] = server;
  row[m_Columns.m_col_customer] = customer;
  row[m_Columns.m_col_state] = state;
  row[m_Columns.m_col_price] = price;

  //child row
  Gtk::TreeModel::Row childrow = *(m_refTreeModel->append(row.children()));
  std::string servings = controller.get_emporium().servings_to_string(order_index);
  childrow[m_Columns.m_col_server] = "### S E R V I N G  I N F O ###\n\n\n"+ servings;
}

void Main_window:: add_rows () {
  Person* person_ptr = controller.get_person_ptr();
  for (int i = 0 ; i< controller.get_emporium().number_of_orders();i++){
     int id = i;
     int order_index = i;
     std::string server = controller.get_emporium().get_orders()[order_index]->get_server().get_name();
     std::string customer = controller.get_emporium().get_orders()[order_index]->get_customer().get_name();
     if (person_ptr->get_name() == customer){
       Gtk::TreeModel::Row row = *(m_refTreeModel->append());
       std::string state = controller.get_emporium().get_orders()[order_index]->get_state_string();
       std::string price = std::to_string(controller.get_emporium().get_orders()[order_index]->get_price());
       row[m_Columns.m_col_id] = id;
       row[m_Columns.m_col_server] = server;
       row[m_Columns.m_col_customer] = customer;
       row[m_Columns.m_col_state] = state;
       row[m_Columns.m_col_price] = price;
       //child row
       Gtk::TreeModel::Row childrow = *(m_refTreeModel->append(row.children()));
       std::string servings = controller.get_emporium().servings_to_string(order_index);
       childrow[m_Columns.m_col_server] = "### S E R V I N G  I N F O ###\n\n\n"+ servings;
     }
     else if (person_ptr->type()== "Owner" || person_ptr->type()== "Manager"|| person_ptr->type()== "Server")  {
       Gtk::TreeModel::Row row = *(m_refTreeModel->append());
       std::string state = controller.get_emporium().get_orders()[order_index]->get_state_string();
       std::string price = std::to_string(controller.get_emporium().get_orders()[order_index]->get_price());
       row[m_Columns.m_col_id] = id;
       row[m_Columns.m_col_server] = server;
       row[m_Columns.m_col_customer] = customer;
       row[m_Columns.m_col_state] = state;
       row[m_Columns.m_col_price] = price;
       //child row
       Gtk::TreeModel::Row childrow = *(m_refTreeModel->append(row.children()));
       std::string servings = controller.get_emporium().servings_to_string(order_index);
       childrow[m_Columns.m_col_server] = "### S E R V I N G  I N F O ###\n\n\n"+ servings;
     } 
  }

}

