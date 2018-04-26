
 #ifndef __STATE_H
 #define __STATE_H 
 #include <iostream>
 #include <string>
 class State {
   public:
     State(int val) : value(val) { }

     static const int unfilled = 0;
     static const int filled = 1;
     static const int paid = 2;
     static const int canceled = 3;


     std::string to_string() {
       switch(value) {
         case(unfilled):return "unfilled";
         case(filled):return "filled";
         case(paid):return "paid";
         case(canceled):return "canceled";
         default: return "UNKNOWN";
       }
     }
     int get_value() { return value;}
   private:
     int value = 0;
 };
 #endif
