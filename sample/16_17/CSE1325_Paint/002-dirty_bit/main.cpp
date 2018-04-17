#include "view.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>

int main(int argc, char** argv)
{
   // Create the application
   auto app = Gtk::Application::create(argc, argv, "edu.uta.cse1325.turtle1");

   // Instance a window
   Gtk::Window win;
   win.set_title("CSE1325 Paint");

   // Instance a drawing surface containing the lines and add to the window
   View view{win};
   win.add(view);
   view.show();

   // Allow view to determine if closing is permitted
   win.signal_delete_event().connect(sigc::mem_fun(view, &View::on_my_delete_event));

   // Return gtkmm's result code to the OS
   return app->run(win);
}
