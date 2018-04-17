
 #include "age.h"
 #include <iostream>

 int main() {

   Age m1(Age::restricted);
   if (m1.to_string() != "restricted") {
     std::cerr << "restricted failed: got " << m1.to_string() << std::endl;
     return -1;
   }

   return 0;
 }
