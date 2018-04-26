#include "server.h"


Server::Server(std::istream& ist){
   std::getline (ist, name);
   ist >> id >> active
       >> hour_salary >> num_order_filled; 
}

std::string Server::type() {return "Server";}

double Server::get_hour_salary() const {return hour_salary; }
int Server::get_num_order_filled() const {return num_order_filled;}
void Server::reset_num_order_filled() {num_order_filled = 0;}    

void Server::add_order_filled(){num_order_filled+=1;}

    void Server::save(std::ostream& ost){
       ost << type() << std::endl 
           << name << std::endl 
           << id << ' ' << active << ' '
           << hour_salary << ' ' << num_order_filled << ' ';
    }

