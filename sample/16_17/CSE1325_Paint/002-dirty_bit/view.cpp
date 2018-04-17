#include "view.h"
#include "line.h"
#include <vector>
#include <gtkmm.h>
#include <cairomm/context.h>
#include <iostream>

using namespace std;

View::View(Gtk::Window& window) : win{window} { }

// True if all data has been written to disk
bool View::saved() {
    return !dirty;
}

// Draw the lines any time gtkmm needs to refresh the widget
bool View::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    // If nothing to draw, we're done
    if (lines.size() == 0) return true;

    // Create a Cairomm context to manage our drawing
    Gtk::Allocation allocation = get_allocation();

    // Center the drawing in the window
    const double width = allocation.get_width();
    const double height = allocation.get_height();
    cr->translate(width / 2, height / 2);

    // Use a 3 pixel wide red line
    cr->set_line_width(3.0);
    cr->set_source_rgb(0.8, 0.0, 0.0); // Set lines to red

    // Draw the lines
    for(Line l : lines) {
        cr->move_to(l.x1(), l.y1());
        cr->line_to(l.x2(), l.y2());
    }

    // Apply the colors to the window
    cr->stroke();

    // Drawing was successful
    return true;
}

bool View::on_my_delete_event(GdkEventAny* event) {
  if (saved()) return false;
  Gtk::MessageDialog d{win, "Unsaved data will be lost", false, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_NONE};
  d.add_button("Save", 1);
  d.add_button("Discard", 2);
  d.add_button("Cancel", 3);
  int response = d.run();
  if (response == 1) {
    cout << "Saving data, then exit" << endl;
    return false;
  } else if (response == 2) {
    cout << "Discarding data and exiting" << endl;
    return false;
  } else {
    return true;
  }
}

