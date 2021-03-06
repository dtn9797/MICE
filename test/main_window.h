#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controller.h"
#include <iostream>
#include <gtkmm.h>
#include <vector>
#include <string>
#include <sigc++/functors/slot.h>
#include "emporium.h"


class Main_window: public Gtk::Window {
  public: 
    Main_window (Controller& con);
    virtual ~Main_window();
  private:
    Controller& controller;
    void create_menu_items(Gtk::MenuBar *menubar, std::string name, std::vector<std::string> sub_names);
    void create_submenu_items(Gtk::Menu *namemenu, std::string name, sigc::slot<void> s);

    Gtk::Box *vbox;
  protected:
    void on_test_click();
    void on_quit_click();
};


#endif
