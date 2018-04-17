#include "turtle.h"
#include "view.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>

int main(int argc, char** argv)
{
   // Create the application
   auto app = Gtk::Application::create(argc, argv, "edu.uta.cse1325.turtle1");

   // Instance a window
   Gtk::Window win;
   win.set_title("Turtle Graphics");

   // Create the vector of lines using Turtle Graphics
   Turtle_graphics g;
   g.penDown();
   for (double d=0; d<20; ++d) {
     g.forward(d*15.0);
     g.turn(144);
   }

   // Instance a drawing surface containing the lines and add to the window
   View view{g.get_lines()};
   win.add(view);
   view.show();

   return app->run(win);
}
