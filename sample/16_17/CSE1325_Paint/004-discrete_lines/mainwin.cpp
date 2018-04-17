#include "mainwin.h"
#include "view.h"


Mainwin::Mainwin() {

    // /////////////////
    // G U I   S E T U P
    // /////////////////

    set_default_size(640, 480);

    // 
    // V B O X -- The window contains a vertical box
    //
    Gtk::Box *vbox = Gtk::manage(new Gtk::Box{Gtk::ORIENTATION_VERTICAL, 0});
    add(*vbox);

    // 
    // M E N U -- The VBox contains a menu at the top
    //
    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar{});
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);

    //     F I L E
    // Create a File menu and add to the menu bar
    Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem{"_File", true});
    menubar->append(*menuitem_file);
    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu{});
    menuitem_file->set_submenu(*filemenu);

    //         Q U I T
    // Append Quit to the File menu
    Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem{"_Quit", true});
    menuitem_quit->signal_activate().connect(sigc::mem_fun(*this, 
        &Mainwin::on_quit_click));
    filemenu->append(*menuitem_quit);

    //
    // V I E W -- The VBox contains a View (DrawingArea) as its next member
    //
    View *view = Gtk::manage(new View{*this});
    vbox->pack_start(*view);
    view->show();

    vbox->show_all();

   // /////////////
   // S I G N A L S 
   // /////////////

   // Allow view to determine if closing is permitted
   signal_delete_event().connect(sigc::mem_fun(view, &View::on_my_delete_event));

}

Mainwin::~Mainwin() { }

void Mainwin::on_quit_click() {
    close();  // This is equivalent to clicking the 'x' in the window manager
              // (Otherwise, we would use hide() instead.)
}
