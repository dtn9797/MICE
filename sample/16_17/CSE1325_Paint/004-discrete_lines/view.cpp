#include "view.h"
#include "line.h"
#include <vector>
#include <gtkmm.h>
#include <cairomm/context.h>

using namespace std;

View::View(Gtk::Window& window) : win{window} { 
    add_events(Gdk::BUTTON_PRESS_MASK);
}

// True if all data has been written to disk
bool View::saved() {
    return !dirty;
}

// Add a line to the vector
void View::new_line(int _x1, int _y1, int _x2, int _y2) {
    lines.push_back(Line(_x1, _y1, _x2, _y2));
    dirty = true;
}

bool View::on_button_press_event(GdkEventButton * event) {
    // If this is a left-mouse button press, we're interested!
    if( (event->type == GDK_BUTTON_PRESS) && (event->button == 1)) {

        // Just remember the coordinates on the first click, but
        // add a new line on the second click
        if (!click_in_progress) {
            x1 = event->x;
            y1 = event->y;
            click_in_progress = true;
        } else {
            new_line(x1, y1, event->x, event->y);
            click_in_progress = false;
            queue_draw();  // initiate screen refresh
        }
        return true; // We handled this event
    }
    return false;  // We did NOT handle this event
}

// Draw the lines any time gtkmm needs to refresh the widget
bool View::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    // If nothing to draw, we're done
    if (lines.size() == 0) return true;

    // Create a Cairomm context to manage our drawing
    Gtk::Allocation allocation = get_allocation();

    // Center the drawing in the window
    // const double width = allocation.get_width();
    // const double height = allocation.get_height();
    // cr->translate(width / 2, height / 2);

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
    // Save data and exit
    return false;
  } else if (response == 2) {
    // Discard data and exit
    return false;
  } else {
    return true;
  }
}

