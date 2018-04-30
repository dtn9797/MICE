#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "emporium.h"
#include "view.h"
#include "person.h"
#include <string>
#include <vector>
class Controller {
  private: 
    Emporium& emporium;
    View view;
    Person* person_ptr; 
    int order_id = -1;
  public:
    Controller (Emporium& emp):emporium{emp}, view{View(emporium)} {}
    Emporium& get_emporium () ;
    void cli ();
    void execute_cmd (int cmd);
    void set_person (Person* per);
    Person* get_person_ptr();
};


#endif
