#include "mainwin.h"
#include "view.h"
#include <iostream>
#include <fstream>

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

    // ///////
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

    //         N E W
    // Append New to the File menu
    Gtk::MenuItem *menuitem_new = Gtk::manage(new Gtk::MenuItem{"_New", true});
    menuitem_new->signal_activate().connect(sigc::mem_fun(*this, 
        &Mainwin::on_new_click));
    filemenu->append(*menuitem_new);

    //         S A V E
    // Append Save to the File menu
    Gtk::MenuItem *menuitem_save = Gtk::manage(new Gtk::MenuItem{"_Save", true});
    menuitem_save->signal_activate().connect(sigc::mem_fun(*this, 
        &Mainwin::on_save_click));
    filemenu->append(*menuitem_save);

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

    //         W I D T H
    // Append Width to the Pen menu
    Gtk::MenuItem *menuitem_width = Gtk::manage(new Gtk::MenuItem{"_Width", true});
    menuitem_width->signal_activate().connect(sigc::mem_fun(*this,
        &Mainwin::on_width_click));
    penmenu->append(*menuitem_width);


    // /////////////
    // T O O L B A R -- Add a toolbar to the vertical box below the menu
    //
    Gtk::Toolbar *toolbar = Gtk::manage(new Gtk::Toolbar);
    vbox->add(*toolbar);

    //     N E W   D R A W I N G
    // Start a new drawing
    Gtk::ToolButton *new_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::NEW));
    new_button->set_tooltip_markup("Start a new drawing, discarding any existing work");
    new_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_new_click));
    toolbar->append(*new_button);

    //     S A V E   D R A W I N G
    // Save a drawing to the default filename
    Gtk::ToolButton *save_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::SAVE));
    save_button->set_tooltip_markup("Save drawing to the default filename");
    save_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_save_click));
    toolbar->append(*save_button);

    //     P E N   C O L O R
    // Add a new pen color icon
    Gtk::Image *button_pen_color_image = Gtk::manage(new Gtk::Image("select_pen_color.png"));
    Gtk::ToolButton *button_pen_color = Gtk::manage(new Gtk::ToolButton(*button_pen_color_image));
    button_pen_color->set_tooltip_markup("Select pen color");
    button_pen_color->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_color_click));
    toolbar->append(*button_pen_color);

    //     P E N   W I D T H
    // Add a set pen width icon
    Gtk::Image *button_pen_width_image = Gtk::manage(new Gtk::Image("select_pen_width.png"));
    Gtk::ToolButton *button_pen_width = Gtk::manage(new Gtk::ToolButton(*button_pen_width_image));
    button_pen_width->set_tooltip_markup("Select pen width");
    button_pen_width->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_width_click));
    toolbar->append(*button_pen_width);


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

//
// The user wants a new, empty drawing
//
void Mainwin::on_new_click() {
    view->new_drawing();
}

//
// The user wants to save the current drawing to the default filename
//
void Mainwin::on_save_click() {
    std::ofstream ofs{view->get_filename(), std::ofstream::out};
    view->save(ofs);
}

//
// The user wants to exit the application
//
void Mainwin::on_quit_click() {
    close();  // This is equivalent to clicking the 'x' in the window manager
              // (Otherwise, we would use hide() instead.)
}

//
// The user wants to change the line color
//
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

//
// The user wants to change the line width
//
void Mainwin::on_width_click() {

    // Create a custom dialog for setting line width
    Gtk::Dialog dialog{"Select Pen Width", *this};

    // The lower widget is a slider (Gtk "scale"), so the user can mouse the new width
    Gtk::Scale scale{};
    scale.set_range(1.0,10.0);
    scale.set_value(view->get_pen_width());
    scale.show();
    dialog.get_vbox()->pack_start(scale);

    // OK and Cancel buttons
    dialog.add_button("Cancel", 0);
    dialog.add_button("OK", 1);
    dialog.set_default_response(1);

    // Show the dialog, get the button pressed
    dialog.show_all();
    int result = dialog.run();
    if (result == 1) view->set_pen_width(scale.get_value());
    dialog.close();
}

