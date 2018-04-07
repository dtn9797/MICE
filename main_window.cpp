#include "main_window.h"
#include <vector>
Main_window::Main_window (Controller& con): controller{con} {
  //
  //GUI SETUP
  //
  set_default_size (768,768);

  //Put verticalbox container
  Gtk::Box *vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
  add(*vbox);
  vbox->show_all();
}

Main_window::~Main_window() { }
