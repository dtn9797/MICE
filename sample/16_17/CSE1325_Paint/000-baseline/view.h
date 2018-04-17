#ifndef _VIEW_H
#define _VIEW_H

#include "line.h"
#include <vector>
#include <gtkmm/drawingarea.h>

using namespace std;

//
// Simple lines in a window
//

class View : public Gtk::DrawingArea {
     vector<Line> lines;
  public:
     View(vector<Line> L);
     bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};
#endif
