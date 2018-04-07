#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controller.h"
#include <gtkmm.h>

class Main_window: public Gtk::Window {
  public: 
    Main_window (Controller& con);
    virtual ~Main_window();
  private:
    Controller& controller;
};


#endif
