 #include "patron.h"

 std::string Patron::to_string() {return name + " (" + number + ")";}

 std::string Patron::get_patron_name() {return name;}
 std::string Patron::get_patron_phone_number() {return number;}

