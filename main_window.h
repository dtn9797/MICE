#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controller.h"
#include <iostream>
#include <gtkmm.h>
#include <vector>
#include <string>
#include <sigc++/functors/slot.h>
#include "person.h"


class Main_window: public Gtk::Window {
  public: 
    Main_window (Controller& con);
    virtual ~Main_window();
  private:
    Controller& controller;
    void create_menu_items(Gtk::MenuBar *menubar, std::string name, std::vector<std::string> sub_names);
    void create_submenu_items(Gtk::Menu *namemenu, std::string name, sigc::slot<void> s);
    void create_toggletoolbuttons_with_toolbar (Person *person, Gtk::Box *vbox)  ;
    void show_window_for_person();
    //Persons
    void show_window_for_owner(Person* person);
    void show_window_for_manager(Person* person);
    void show_window_for_server(Person* person);
    void show_window_for_customer(Person* person);
    //Utilities
    Gtk::ToggleToolButton *manager_button;
    Gtk::ToggleToolButton *owner_button;
    Gtk::ToggleToolButton *customer_button;
    Gtk::ToggleToolButton *server_button;
    Gtk::ToolButton *switch_person_button;
  protected:
    void on_quit_click();
    void on_properties_click();
    void on_create_order_click();
    void on_create_item_click();

    void on_switch_person_click();

    void on_test_click();
};


#endif
