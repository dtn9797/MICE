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
    //Tree View
    void add_row (int order_index);
    //Persons
    void show_window_for_owner(Person* person);
    void show_window_for_manager(Person* person);
    void show_window_for_server(Person* person);
    void show_window_for_customer(Person* person);
    //Utilities
    Gtk::Box *vbox;
    Gtk::ToggleToolButton *manager_button;
    Gtk::ToggleToolButton *owner_button;
    Gtk::ToggleToolButton *customer_button;
    Gtk::ToggleToolButton *server_button;
    Gtk::ToolButton *switch_person_button;
    //Tree View
    
  protected:
    void on_quit_click();
    void on_properties_click();
    void on_create_order_click();
    void on_create_item_click();

    void on_switch_person_click();

    void on_test_click();

    void on_treeview_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
    class ModelColumns : public Gtk::TreeModel::ColumnRecord{
      public:
          ModelColumns(){
          add (m_col_id);
          add (m_col_server);
          add (m_col_customer);
          add (m_col_state);
          add (m_col_price);
        }
        Gtk::TreeModelColumn<int> m_col_id;
        Gtk::TreeModelColumn<Glib::ustring> m_col_server;
        Gtk::TreeModelColumn<Glib::ustring> m_col_customer;
        Gtk::TreeModelColumn<Glib::ustring> m_col_state;
        Gtk::TreeModelColumn<Glib::ustring> m_col_price;
    };
    
    ModelColumns m_Columns;  
    Gtk::ScrolledWindow m_ScrolledWindow;
    Gtk::TreeView m_TreeView;
    Glib::RefPtr<Gtk::TreeStore> m_refTreeModel;
    //Gtk::ButtonBox m_ButtonBox;

};


#endif
