#ifndef _VIEW_H
#define _VIEW_H

#include "line.h"
#include <vector>
#include <gtkmm/drawingarea.h>

using namespace std;

class View : public Gtk::DrawingArea {
  public:
     View(Gtk::Window& window);
     bool saved();
     bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
     bool on_my_delete_event(GdkEventAny* event);
  private:
     Gtk::Window& win;
     vector<Line> lines;
     bool dirty = true;  // True if any changes since last save
};
#endif
