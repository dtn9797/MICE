 #include "publication.h"
 #include <string>
 #include <iostream>

 bool Publication::is_checked_out() {return checked_out;}
 void Publication::check_out(Patron& p_patron) {
   if (checked_out) {
     throw Invalid_transaction();
   } else {
     patron = p_patron;
     checked_out = true;
   }
 }
   
 void Publication::check_in() {
   if (checked_out) {
     checked_out = false;
   } else {
     throw Invalid_transaction();
   }
 }

 std::string Publication::to_string() {
   std::string pub = "\"" + title + "\"" + " by " + author + ", \n      " + copyright + 
     " (" + target_age.to_string() + " " + genre.to_string() + " "  
         + media.to_string() + ") \n      " + "ISBN: " + isbn;
   if (checked_out) {
      pub += "\n      Checked out to " + patron.get_patron_name() + 
             " (" + patron.get_patron_phone_number() + ")";
   }
   return pub;
 }

 std::vector<std::string> Publication::to_strings() {
   std::vector<std::string> strings;
   strings.push_back(title);
   strings.push_back(author);
   strings.push_back(copyright);
   strings.push_back(target_age.to_string());
   strings.push_back(genre.to_string());
   strings.push_back(media.to_string());
   strings.push_back(isbn);
   strings.push_back(checked_out ? patron.get_patron_name() : "");
   strings.push_back(checked_out ? patron.get_patron_phone_number() : "");
   return strings;
 }

