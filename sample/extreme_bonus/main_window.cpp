#include "main_window.h"
#include <vector>

Main_window::Main_window(Controller& controller) : _controller{controller} {

    // /////////////////
    // G U I   S E T U P
    // /////////////////

    set_default_size(1024, 768);

    // Put a vertical box container as the Window contents
    Gtk::Box *vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    add(*vbox);

    // ///////
    // M E N U
    // Add a menu bar as the top item in the vertical box
    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar());
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);

    //     F I L E
    // Create a File menu and add to the menu bar
    Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    menubar->append(*menuitem_file);
    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);

    //         T E S T
    // Append Test (the "Easter egg") to the File menu
    Gtk::MenuItem *menuitem_test = Gtk::manage(new Gtk::MenuItem("_Test", true));
    menuitem_test->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_test_click));
    filemenu->append(*menuitem_test);


    //         Q U I T
    // Append Quit to the File menu
    Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    menuitem_quit->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_quit_click));
    filemenu->append(*menuitem_quit);

    //     P U B L I C A T I O N
    // Create a Publication menu and add to the menu bar
    Gtk::MenuItem *menuitem_publication = Gtk::manage(new Gtk::MenuItem("_Publication", true));
    menubar->append(*menuitem_publication);
    Gtk::Menu *publicationmenu = Gtk::manage(new Gtk::Menu());
    menuitem_publication->set_submenu(*publicationmenu);

    //         L I S T
    // Append Quit to the File menu
    Gtk::MenuItem *menuitem_listpubs = Gtk::manage(new Gtk::MenuItem("_List", true));
    menuitem_listpubs->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_list_pubs_click));
    publicationmenu->append(*menuitem_listpubs);

    //         A D D
    // Append Add to the Publication menu
    Gtk::MenuItem *menuitem_addpub = Gtk::manage(new Gtk::MenuItem("_Add", true));
    menuitem_addpub->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_add_pub_click));
    publicationmenu->append(*menuitem_addpub);

    //         C H E C K   O U T
    // Append Check Out to the Publication menu
    Gtk::MenuItem *menuitem_checkout = Gtk::manage(new Gtk::MenuItem("Check _Out", true));
    menuitem_checkout->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_checkout_click));
    publicationmenu->append(*menuitem_checkout);

    //         C H E C K   I N
    // Append Check In to the Publication menu
    Gtk::MenuItem *menuitem_checkin = Gtk::manage(new Gtk::MenuItem("Check _In", true));
    menuitem_checkin->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_checkin_click));
    publicationmenu->append(*menuitem_checkin);

    //     P A T R O N
    // Create a Patron menu and add to the menu bar
    Gtk::MenuItem *menuitem_patron = Gtk::manage(new Gtk::MenuItem("Patro_n", true));
    menubar->append(*menuitem_patron);
    Gtk::Menu *patronmenu = Gtk::manage(new Gtk::Menu());
    menuitem_patron->set_submenu(*patronmenu);

    //         L I S T
    // Append List to the Patron menu
    Gtk::MenuItem *menuitem_listpatrons = Gtk::manage(new Gtk::MenuItem("_List", true));
    menuitem_listpatrons->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_list_patrons_click));
    patronmenu->append(*menuitem_listpatrons);

    //         A D D
    // Append Add to the Patron menu
    Gtk::MenuItem *menuitem_addpatron = Gtk::manage(new Gtk::MenuItem("_Add", true));
    menuitem_addpatron->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_add_patron_click));
    patronmenu->append(*menuitem_addpatron);

    //     H E L P
    // Create a Help menu and add to the menu bar
    Gtk::MenuItem *menuitem_help = Gtk::manage(new Gtk::MenuItem("_Help", true));
    menubar->append(*menuitem_help);
    Gtk::Menu *helpmenu = Gtk::manage(new Gtk::Menu());
    menuitem_help->set_submenu(*helpmenu);

    //           M A N U A L
    // Append Manual to the Help menu
    Gtk::MenuItem *menuitem_manual = Gtk::manage(new Gtk::MenuItem("_Manual", true));
    menuitem_manual->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_manual_click));
    helpmenu->append(*menuitem_manual);

    //           A B O U T
    // Append About to the Help menu
    Gtk::MenuItem *menuitem_about = Gtk::manage(new Gtk::MenuItem("_About", true));
    menuitem_about->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_about_click));
    helpmenu->append(*menuitem_about);

    // /////////////
    // T O O L B A R
    
    // Add a toolbar to the vertical box below the menu
    Gtk::Toolbar *toolbar = Gtk::manage(new Gtk::Toolbar);
    vbox->add(*toolbar);

    //     N E W   P U B L I C A T I O N
    // Add a new publication
    Gtk::ToolButton *new_pub_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::NEW));
    new_pub_button->set_tooltip_markup("Create a new publication");
    new_pub_button->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_add_pub_click));
    toolbar->append(*new_pub_button);

    //     L I S T   P U B L I C A T I O N S
    // List all publications
    Gtk::ToolButton *list_pubs_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::INDEX));
    list_pubs_button->set_tooltip_markup("List all publications");
    list_pubs_button->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_list_pubs_click));
    toolbar->append(*list_pubs_button);

    //     C H E C K O U T
    // Check out a publication
    Gtk::Image *checkout_image = Gtk::manage(new Gtk::Image("checkout.png"));
    Gtk::ToolButton *checkout_button = Gtk::manage(new Gtk::ToolButton(*checkout_image));
    checkout_button->set_tooltip_markup("Check out a publication");
    checkout_button->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_checkout_click));
    toolbar->append(*checkout_button);

    //     C H E C K I N
    // Check in a publication
    Gtk::Image *checkin_image = Gtk::manage(new Gtk::Image("checkin.png"));
    Gtk::ToolButton *checkin_button = Gtk::manage(new Gtk::ToolButton(*checkin_image));
    checkin_button->set_tooltip_markup("Check in a publication");
    checkin_button->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_checkin_click));
    toolbar->append(*checkin_button);

    // -----------------------

    Gtk::SeparatorToolItem *sep1 = Gtk::manage(new Gtk::SeparatorToolItem());
    toolbar->append(*sep1);

    //     A D D   P A T R O N
    // Add a Patron
    Gtk::Image *addpatron_image = Gtk::manage(new Gtk::Image("add_patron.png"));
    Gtk::ToolButton *addpatron_button = Gtk::manage(new Gtk::ToolButton(*addpatron_image));
    addpatron_button->set_tooltip_markup("Add a Patron");
    addpatron_button->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_add_patron_click));
    toolbar->append(*addpatron_button);

    //     L I S T   P A T R O N S
    // List all Patrons
    Gtk::Image *listpatrons_image = Gtk::manage(new Gtk::Image("list_patrons.png"));
    Gtk::ToolButton *listpatrons_button = Gtk::manage(new Gtk::ToolButton(*listpatrons_image));
    listpatrons_button->set_tooltip_markup("List All Patrons");
    listpatrons_button->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_list_patrons_click));
    toolbar->append(*listpatrons_button);

    // -----------------------

    Gtk::SeparatorToolItem *sep = Gtk::manage(new Gtk::SeparatorToolItem());
    sep->set_expand(true);  // The expanding sep forces the Quit button to the right
    toolbar->append(*sep);

    //     H E L P
    // Add a icon for quitting
    Gtk::ToolButton *help_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::HELP));
    help_button->set_tooltip_markup("Help");
    help_button->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_manual_click));
    toolbar->append(*help_button);

    //     Q U I T
    // Add a icon for quitting
    Gtk::ToolButton *quit_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::QUIT));
    quit_button->set_tooltip_markup("Exit LMS");
    quit_button->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_quit_click));
    toolbar->append(*quit_button);

    // P U B L I C A T I O N   T A B L E

    _tree_model = Gtk::ListStore::create(_columns);

    _tree_view.set_model(_tree_model);

    _tree_view.append_column("ID", _columns.m_pub_id);
    _tree_view.append_column("Title", _columns.m_pub_name);
    _tree_view.append_column("Author", _columns.m_author);
    _tree_view.append_column("Copyright", _columns.m_copyright);
    _tree_view.append_column("Target Age", _columns.m_age);
    _tree_view.append_column("Genre", _columns.m_genre);
    _tree_view.append_column("Media", _columns.m_media);
    _tree_view.append_column("ISBN", _columns.m_isbn);
    _tree_view.append_column("Patron", _columns.m_patron);
    _tree_view.append_column("Patron Phone", _columns.m_patron_phone);

    _swindow.add(_tree_view);
    _swindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    _swindow.set_hexpand(true);
    _swindow.set_vexpand(true);

    vbox->pack_start(_swindow);

/*
    // S T A T U S   B A R   D I S P L A Y
    // Provide a status bar for messages
    msg = Gtk::manage(new Gtk::Label());
    msg->set_hexpand(true);
    vbox->add(*msg);
*/
    // Make the box and everything in it visible
    vbox->show_all();
}

Main_window::~Main_window() { }

// /////////////////
// C A L L B A C K S
// /////////////////

void Main_window::on_test_click() {
    int index = _controller.number_of_pubs();
    _controller.execute_cmd(99);
    for (int i=index; i<_controller.number_of_pubs(); ++i) add_row(i);
}

void Main_window::on_list_pubs_click() {_controller.execute_cmd(2);}
void Main_window::on_add_pub_click() {
    int index = _controller.number_of_pubs();
    _controller.execute_cmd(1);
    for (int i=index; i<_controller.number_of_pubs(); ++i) add_row(i);
}

void Main_window::on_checkout_click() {
    _controller.execute_cmd(3);
    update_rows();
}

void Main_window::on_checkin_click() {
    _controller.execute_cmd(4);
    update_rows();
}

void Main_window::on_list_patrons_click() {_controller.execute_cmd(6);}
void Main_window::on_add_patron_click() {_controller.execute_cmd(5);}
void Main_window::on_manual_click() {_controller.execute_cmd(9);}

void Main_window::on_about_click() {
    Glib::ustring s = "<span size='20000' weight='bold'>Library Management System</span>\n<span size='large'>Copyright 2017 by George F. Rice</span>\n<span size='small'>Licensed under Creative Commons Attribution 4.0 International\nSome icons copyright The Noun Project,\n    used under Creative Commons Attribution License</span>";
    Gtk::MessageDialog dlg(*this, s, true, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
    dlg.run();
}

void Main_window::on_quit_click() {
    hide();
}

// /////////////////
// U T I L I T I E S
// /////////////////

void Main_window::add_row(int index) {
    // Add a new row to the tree model to hold the new publication
    Gtk::TreeModel::Row row = *(_tree_model->append());

    // Load the data into the new row
    std::vector<std::string> record = _controller.pub_to_strings(index);

    row[_columns.m_pub_id] = index;
    row[_columns.m_pub_name] = record[0];
    row[_columns.m_isbn] = record[1];
    row[_columns.m_author] = record[2];
    row[_columns.m_copyright] = record[3];
    row[_columns.m_genre] = record[4];
    row[_columns.m_media] = record[5];
    row[_columns.m_age] = record[6];
    row[_columns.m_patron] = record[7];
    row[_columns.m_patron_phone] = record[8];
}


void Main_window::update_rows() {
    Gtk::TreeIter iter = _tree_model->get_iter("0");
    for(int i=0; i<_controller.number_of_pubs(); ++i) {
        std::vector<std::string> record = _controller.pub_to_strings(i);
        (*iter)[_columns.m_patron] = record[7];
        (*iter)[_columns.m_patron_phone] = record[8];
        iter++;
    }
}

