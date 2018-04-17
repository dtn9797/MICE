#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "controller.h"
#include <gtkmm.h>

class Main_window : public Gtk::Window
{
    public:
        Main_window(Controller& controller);
        virtual ~Main_window();
    protected:
        void on_list_pubs_click();        // Create a new publication
        void on_add_pub_click();          // Add a new publication
        void on_checkout_click();         // Checkout an existing publication
        void on_checkin_click();          // Checkout an existing publication
        void on_list_patrons_click();     // List all patrons
        void on_add_patron_click();       // Add a patron
        void on_manual_click();           // Display Help dialog
        void on_about_click();            // Display About dialog
        void on_quit_click();             // Exit the LMS
        void on_test_click();             // "Easter egg"

        // This nested class (Main_window::ModelColums) represents
        //   the columns we'll display as part of our tree view below.
        // We define each column by instancing the TreeModelColumn
        //   template, then (in the constructor) use ColumnRecord's
        //   add() method to set up the columns.

        class ModelColumns : public Gtk::TreeModel::ColumnRecord {
            public:
                ModelColumns() {
                    add(m_pub_id);
                    add(m_pub_name);
                    add(m_author);
                    add(m_copyright);
                    add(m_age);
                    add(m_genre);
                    add(m_media);
                    add(m_isbn);
                    add(m_patron);
                    add(m_patron_phone);
                }

            Gtk::TreeModelColumn<unsigned int> m_pub_id;
            Gtk::TreeModelColumn<Glib::ustring> m_pub_name;
            Gtk::TreeModelColumn<Glib::ustring> m_author;
            Gtk::TreeModelColumn<Glib::ustring> m_copyright;
            Gtk::TreeModelColumn<Glib::ustring> m_age;
            Gtk::TreeModelColumn<Glib::ustring> m_genre;
            Gtk::TreeModelColumn<Glib::ustring> m_media;
            Gtk::TreeModelColumn<Glib::ustring> m_isbn;
            Gtk::TreeModelColumn<Glib::ustring> m_patron;
            Gtk::TreeModelColumn<Glib::ustring> m_patron_phone;

        };

        // The instance we'll actually use. C programmers would
        //   probably put _columns between the } and ; above,
        //   which is permissible per the language spec.
        ModelColumns _columns;

        // The tree model holds the data to be displayed.
        // In the real world (if we were starting from scratch),
        //   our Library class would implement the Gtk::TreeModel
        //   interface, and thus serve as the tree model directly.
        // As with accounting, keeping 2 sets of books ends badly.
        // But we're easing into GUIs, so... two sets of books it is!

        Glib::RefPtr<Gtk::ListStore> _tree_model;

        // The tree view is one GUI presentation of the tree model data.
        // You can create as many different views as you like, and they
        //   will each dutifully track changes to the tree model data.

        Gtk::TreeView _tree_view;

        // The scroll window is a container that will hold our tree view.
        // Any time the entire tree view won't fit within the scroll
        //   window, the latter will create scroll bars and display only
        //   a moveable portion of the data.

        Gtk::ScrolledWindow _swindow;

        // This utility method syncs a (usually new) row from the library
        //   to the tree model, so that the tree view will display it

        void add_row(int index);

        // This utility method updates the patron name and phone number
        //   for all publications in the library, usually after a check out
        //   or check in.

        void update_rows();

    private:
        Gtk::Label *msg;                  // Status message display
        Controller& _controller;          // The controller instance for LMS
};
#endif 

