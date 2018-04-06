#include "emporium.h"

    void Emporium::add_scoop(Scoop* scoop) {scoops.push_back(scoop);}
    void Emporium::add_top(Topping* top) {tops.push_back(top);}
    void Emporium::add_container(Container* con) {containers.push_back(con);}

    std::string Emporium::scoop_to_string(int index) {return scoops[index]->to_string();}
    std::string Emporium::top_to_string(int index) {return tops[index]->to_string();}
    std::string Emporium::container_to_string(int index) {return containers[index]->to_string();}

    int Emporium::number_of_scoop() {scoops.size();}
    int Emporium::number_of_top() {tops.size();}
    int Emporium::number_of_container() {containers.size();}

    void Emporium::auto_add() {
      add_scoop(new Scoop ("Vanilla","General",1,1));
      add_scoop(new Scoop ("Cookies", "Sweet",1,1));

      add_top(new Topping ("Light","General",1,1));
      add_top(new Topping ("Normal", "Sweet",1,1));

      add_container(new Container ("Cups","General",1,1,1));
      add_container(new Container ("Bowls", "Sweet",1,1,1));
       
    }
