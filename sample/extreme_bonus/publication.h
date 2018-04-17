 #ifndef __PUBLICATION_H
 #define __PUBLICATION_H 
 #include "patron.h"
 
 #include "media.h"
 #include "genre.h"
 #include "age.h"

 #include <iostream>
 #include <string>
 #include <vector>

 class Publication {
   public:
     Publication(std::string p_title, 
                 std::string p_author, 
                 std::string p_copyright,
                 Genre p_genre, 
                 Media p_media, 
                 Age p_target_age,
                 std::string p_isbn) : 

                 title(p_title), 
                 author(p_author),
                 copyright(p_copyright), 
                 genre(p_genre), 
                 media(p_media),
                 target_age(p_target_age), 
                 isbn(p_isbn), 
                 patron(Patron()),
                 checked_out(false) { }

     bool is_checked_out();

     void check_out(Patron& patron);
     void check_in();

     std::string to_string();
     std::vector<std::string> to_strings();

     // Thrown on check_in if publication isn't checked out
     //   or on cheeck_out if publication is already checked out
     class Invalid_transaction { }; 

   private:
     std::string title;
     std::string author;
     std::string copyright;
     Genre genre;
     Media media;
     Age target_age;
     std::string isbn;
     Patron patron;
     bool checked_out;
 };
 #endif
