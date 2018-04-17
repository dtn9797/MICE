
 #include "media.h"
 #include <iostream>

 int main() {

   Media m1(Media::video);
   if (m1.to_string() != "video") {
     std::cerr << "video failed: got " << m1.to_string() << std::endl;
     return -1;
   }

   return 0;
 }
