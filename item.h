#ifndef __ITEMS_H
#define __ITEMS_H 

#include <iostream>
#include <string>

//
//POLYMORPHISM
//

class Item {
  public:
    Item (std::string n,std::string d, double c, double p, std::string i= ""):
      name{n},
      description{d},
      wholesale_cost{c},
      retail_price{p},
      stock_remaining{25},
      image_name{i} {}
    /*Item (std::string n0,std::string d0, double c0, double p0, std::string i0):
      name{n0},
      description{d0},
      wholesale_cost{c0},
      retail_price{p0},
      stock_remaining{25} {image = Gtk::Image(i0);}*/
    Item (): Item("","",0,0){}
     void restock (int amount =25);
     void consume (int amount =1);
     virtual std::string type();
     virtual std::string to_string();
     virtual void save(std::ostream& ost);

     std::string get_name ()const ;
     std::string get_description () const ;
     double get_wholesale_cost ()const ;
     double get_retail_price();
     std::string get_image_name() const;
     int get_stock_remaining();
     bool operator== (const Item& rhs);
  protected:
    std::string name;
    std::string description;
    double wholesale_cost=0;
    double retail_price=0;
    int stock_remaining=25;
    std::string image_name;
};

#endif
