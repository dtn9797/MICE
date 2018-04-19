#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "emporium.h"
#include <string>
#include <vector>
class Controller {
  private: 
    Emporium& emporium;
  public:
    Controller (Emporium& emp):emporium{emp} {}
    Emporium& get_emporium () ;
    void cli ();
    void execute_cmd (int cmd);
    //to string func
    std::vector<std::string> order_to_strings(int index);
};


#endif
