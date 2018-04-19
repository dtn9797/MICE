#include "emporium.h"
#include "controller.h"
#include "main_window.h"
#include <gtkmm.h>
#include <iostream>
int main (int argc, char *argv[]) {
 auto app = Gtk::Application::create (argc, argv,"edu.com.uta.cse1325.mice");
 Emporium em;
 Controller con(em);
 Main_window win(con);
 win.set_title ("Emporium System");
 return app->run(win);
}


