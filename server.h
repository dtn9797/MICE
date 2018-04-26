#ifndef SERVER_H
#define SERVER_H

#include "person.h"
#include <iostream>
#include <string>
class Server : public Person {
  public:
    Server (std::string na, int id, double sal): Person(na,id), hour_salary{sal} {}
    Server () : Server("", 0, 0.0) { }
    Server(std::istream& ist);
    std::string type() override;
    void save(std::ostream& ost) override;
    double get_hour_salary() const;
    int get_num_order_filled() const;
    void reset_num_order_filled();
    void add_order_filled();
  private:
    double hour_salary;
    int num_order_filled=0;
};


#endif
