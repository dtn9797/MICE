#ifndef __VIEW_H
#define __VIEW_H 
 
#include "library.h"

class View {
  public:
    View(Library& lib) : library(lib) { }
    int select_from_menu();
    void list_publications();
    int select_publication();
    void list_patrons();
    int select_patron();
    int select_genre();
    int select_age();
    int select_media();
    void help();
  private:
    std::string get_publications();
    std::string get_patrons();
    Library& library; 
};
#endif
