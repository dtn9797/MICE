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
    Main_window () : Main_window(controller){}
  private:
    Controller& controller;
    void create_menu_items(Gtk::MenuBar *menubar, std::string name, std::vector<std::string> sub_names);
    void create_submenu_items(Gtk::Menu *namemenu, std::string name, sigc::slot<void> s);
    void create_toggletoolbuttons_with_toolbar (Person *person, Gtk::Box *vbox)  ;
    void show_window_for_person();
    //Tree View
    void add_row (int order_index);
    void add_rows ();
    void delete_rows();
    void update_rows();
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
    Gtk::ToolButton *item_button;
    Gtk::ToolButton *order_button;
    Gtk::ToolButton *fill_button;
    Gtk::ToolButton *payment_button;
    Gtk::ToolButton *cancel_button;


        Gtk::MenuItem *menuitem_new;
        Gtk::MenuItem *menuitem_open;
        Gtk::MenuItem *menuitem_save;
        Gtk::MenuItem *menuitem_test;
        Gtk::MenuItem *menuitem_quit;
        Gtk::MenuItem *menuitem_order;
        Gtk::MenuItem *menuitem_customer;
        Gtk::MenuItem *menuitem_item;
        Gtk::MenuItem *menuitem_server;
        Gtk::MenuItem *menuitem_fill_order;
        Gtk::MenuItem *menuitem_pay_for_order;
        Gtk::MenuItem *menuitem_cancel_order;
        Gtk::MenuItem *menuitem_restock;


    
  protected:
    void on_quit_click();
    void on_properties_click();
    void on_create_order_click();
    void on_create_item_click();
    void on_restock_click();
    void on_filled_click();
    void on_cancel_click();
    void on_pay_click();
    void on_save_click();
    void on_save_as_click();
    void on_load_click();
    

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
    Gtk::ScrolledWindow m_ScrolledWindow;
    Gtk::TreeView m_TreeView;
    ModelColumns m_Columns;  
    Glib::RefPtr<Gtk::TreeStore> m_refTreeModel;
    //Gtk::ButtonBox m_ButtonBox;

};


#endif
