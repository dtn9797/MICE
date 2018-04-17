#ifndef _VIEW_H
#define _VIEW_H

#include "line.h"
#include <vector>
#include <gtkmm/drawingarea.h>
#include <iostream>
#include <fstream>

class View : public Gtk::DrawingArea {
  public:
     View(Gtk::Window& window);


     // ////////
     // File I/O

     // Create a blank new drawing
     void new_drawing();

     // Get / set the drawing's current filename
     std::string get_filename();
     void set_filename(std::string new_filename);

     // Save the current drawing to the provided output stream
     void save(std::ostream& os);

     // Load a drawing from the provided input stream
     void load(std::istream& is);



     // ///////////////////
     // Getters and setters

     // Specify pen color for subsequent lines
     void set_pen_color(Gdk::RGBA new_color);
     Gdk::RGBA get_pen_color();

     // Specify pen width for subsequent lines
     void set_pen_width(double new_width);
     double get_pen_width();

     // True if all data has been saved to a file
     bool saved();

     // Set and get pen mode
     int get_pen_mode();
     void set_pen_mode(int new_pen_mode);

     // Set and get dash pattern
     int get_dash_pattern();
     void set_dash_pattern(int new_dash);


     // ////////////////
     // Public constants
     static const int PEN_MODE_SEGMENT = 1;
     static const int PEN_MODE_CONTIGUOUS = 2;
     static const int PEN_MODE_FREEHAND = 3;



     // ///////////////
     // Signal handlers

     // Response to a request from the OS to redraw the window
     bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

     // Response to an attempt to close the main window
     bool on_my_delete_event(GdkEventAny* event);

  protected:
     // Response to a button press
     bool on_button_press_event(GdkEventButton * event) override;

     // Response to dragging the mouse (for scribbling)
     bool on_motion_notify_event(GdkEventMotion * event) override;

  private:


     // ///////////////
     // Private methods

     // Offers to save any unsaved data, returns true of use clicks Cancel
     bool drawing_is_unsaved();



     // //////////////
     // Private fields

     // Main window (as parent for dialogs)
     Gtk::Window& win;   

     // Filename of the currently open drawing
     std::string filename = "untitled.ctp";

     // The current drawing color and opacity
     Gdk::RGBA color = Gdk::RGBA("red");

     // The current drawing width
     int width = 3;

     // Coordinates for most recent click
     int x1, y1;

     // Drawing modes: Segment or Contiguous
     int pen_mode = PEN_MODE_SEGMENT;

     // List of lines already drawn
     std::vector<Line> lines; 

     // Create a new Line and add it to the lines vector
     void new_line(int _x1, int _y1, int _x2, int _y2, Gdk::RGBA _color, double _width, int _dash);
     void new_line(std::istream& is);

     // True if any changes since last save
     bool dirty = false;

     // True to draw line to next click
     bool click_in_progress = false; 

     // Current dash pattern
     int dash = 0;

     // Supported dashed lines
     typedef std::vector<double> dash_pattern;
     std::vector<dash_pattern> dashes = {
         {8.0, 0.0},
         {8.0, 8.0},
         {8.0, 4.0},
         {8.0, 4.0, 2.0, 4.0}
     };
};
#endif
