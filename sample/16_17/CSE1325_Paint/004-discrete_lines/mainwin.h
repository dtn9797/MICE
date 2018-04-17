#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>

class Mainwin : public Gtk::Window {
    public:
        Mainwin();
        virtual ~Mainwin();
    protected:
        void on_quit_click();            // Exit the program
};
#endif
