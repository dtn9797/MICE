#ifndef __CONTROLLER_H
#define __CONTROLLER_H 
 
#include "library.h"
#include "view.h"
#include <vector>

class Controller {
  public:
    Controller (Library& lib) : library(lib), view(View(library)) { }
    void cli();
    void execute_cmd(int cmd);
    int number_of_pubs();
    std::vector<std::string> pub_to_strings(int index);
  private:
    Library& library; 
    View view;
};
#endif
