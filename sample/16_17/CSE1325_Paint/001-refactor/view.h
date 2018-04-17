#ifndef _VIEW_H
#define _VIEW_H

#include "line.h"
#include <vector>
#include <gtkmm/drawingarea.h>

using namespace std;

class View : public Gtk::DrawingArea {
  public:
     View(vector<Line> L);
     bool saved();
     bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
  private:
     vector<Line> lines;
     bool dirty = false;  // True if any changes since last save
};
#endif
