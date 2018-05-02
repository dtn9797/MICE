#include "emporium.h"
#include "controller.h"
#include "main_window.h"
#include <gtkmm.h>
#include <iostream>
#include "owner.h"
int main (int argc, char *argv[]) {
 auto app = Gtk::Application::create (argc, argv,"edu.com.uta.cse1325.mice");
 Emporium em;
 Owner *owner = new Owner ("Default Owner",1);
 em.add_owner(owner);
 Controller con(em);
 con.set_person (owner);
 Main_window win(con);
 win.set_title ("Emporium System");
 return app->run(win);
}
