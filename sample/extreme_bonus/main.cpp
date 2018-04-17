#include <gtkmm.h>
#include "controller.h"
#include "library.h"
#include "main_window.h"

int main(int argc, char *argv[]) {
  auto app = Gtk::Application::create(argc, argv, "edu.uta.cse1325.lms");
  Library library;
  Controller controller(library);
  Main_window win(controller);
  win.set_title("Library Management System");
  return app->run(win);
}
