 #ifndef __PATRON_H
 #define __PATRON_H 
 #include <iostream>
 #include <string>

 class Patron {
   public:
     Patron(std::string patron_name, std::string patron_phone_number) 
       : name(patron_name), number(patron_phone_number) {}
     Patron() : name("unknown"), number("unknown") {}

     std::string to_string();

     std::string get_patron_name();
     std::string get_patron_phone_number();

   private:
     std::string name;
     std::string number;
 };
 #endif
