#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>
#include "view.h"

class Mainwin : public Gtk::Window {
    public:
        Mainwin();
        virtual ~Mainwin();
    protected:
        void on_quit_click();           // Exit the program
        void on_color_click();          // Set the pen color
        void on_width_click();          // Set the pen width
        void on_save_click();           // Save the drawing
    private:
        View *view;                     // The drawing area
};
#endif
