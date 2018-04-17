#include "mainwin.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>

int main(int argc, char** argv)
{
   // Create the application
   auto app = Gtk::Application::create(argc, argv, "edu.uta.cse1325.turtle1");

   // Instance a window
   Mainwin win;
   win.set_title("CSE1325 Paint");

   // Return gtkmm's result code to the OS
   return app->run(win);
}
