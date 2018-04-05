#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "emporium.h"
#include "view.h"

class Controller {
  private: 
    Emporium& emporium;
    View view;
  public:
    Controller (Emporium& emp): emporium{emp}, view{View(emporium)} {}
    void cli ();
    void execute_cmd (int cmd);
};


#endif
