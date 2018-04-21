#include "emporium.h"
#include "controller.h"
#include "main_window.h"
#include <gtkmm.h>
#include <iostream>
#include "owner.h"
int main (int argc, char *argv[]) {
 auto app = Gtk::Application::create (argc, argv,"edu.com.uta.cse1325.mice");
 Emporium em;
 //testing
 Owner *owner = new Owner ("Duy Nguyen",1);
 em.add_owner(owner);
 em.add_manager(new Manager ("Thao Pham",1,2));
 em.add_server(new Server ("Server",1,1));

 Controller con(em);
 Main_window win(con);
 win.set_title ("Emporium System");
 return app->run(win);
}
