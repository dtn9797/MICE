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
   View view{vector<Line>{}};
   win.add(view);
   view.show();

   return app->run(win);
}
