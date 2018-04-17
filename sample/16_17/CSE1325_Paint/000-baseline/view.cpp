#include "view.h"
#include "line.h"
#include <vector>
#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>

using namespace std;

View::View(vector<Line> L) : lines{L} { }

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

