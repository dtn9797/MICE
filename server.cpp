#include "server.h"

std::string Server::type() {return "Server";}

double Server::get_hour_salary(){return hour_salary; }
int Server::get_num_order_filled(){return num_order_filled;}
    
void Server::add_order_filled(){num_order_filled+=1;}
