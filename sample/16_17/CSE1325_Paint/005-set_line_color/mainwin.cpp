#include "mainwin.h"
#include "view.h"


Mainwin::~Mainwin() { }

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

    //     P E N
    // Create a Pen menu and add to the menu bar
    Gtk::MenuItem *menuitem_pen = Gtk::manage(new Gtk::MenuItem{"_Pen", true});
    menubar->append(*menuitem_pen);
    Gtk::Menu *penmenu = Gtk::manage(new Gtk::Menu{});
    menuitem_pen->set_submenu(*penmenu);

    //         C O L O R
    // Append Color to the Pen menu
    Gtk::MenuItem *menuitem_color = Gtk::manage(new Gtk::MenuItem{"_Color", true});
    menuitem_color->signal_activate().connect(sigc::mem_fun(*this,
        &Mainwin::on_color_click));
    penmenu->append(*menuitem_color);


    //
    // V I E W -- The VBox contains a View (DrawingArea) as its next member
    //
    view = Gtk::manage(new View{*this});
    vbox->pack_start(*view);
    view->show();

    vbox->show_all();

   // ///////////////////////////////////
   // S I G N A L   C O N N E C T I O N S
   // ///////////////////////////////////

   // Allow view to determine if closing is permitted
   signal_delete_event().connect(sigc::mem_fun(view, &View::on_my_delete_event));

}

// /////////////////////////////
// S I G N A L   H A N D L E R S
// /////////////////////////////

void Mainwin::on_quit_click() {
    close();  // This is equivalent to clicking the 'x' in the window manager
              // (Otherwise, we would use hide() instead.)
}

void Mainwin::on_color_click() {
  Gtk::ColorChooserDialog dialog("Please choose a color");
  dialog.set_transient_for(*this);

  //Get the previously selected color:
  dialog.set_rgba(view->get_pen_color());

  int result = dialog.run();

  //Handle the response:
  if (result == Gtk::RESPONSE_OK) 
      view->set_pen_color(dialog.get_rgba());
}
