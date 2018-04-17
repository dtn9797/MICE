#include "publication.h"
#include "patron.h"
#include <iostream>

int main() {
  std::string expected = "\"The Firm\" by John Grisham, \n      1991 (adult fiction book) \n      ISBN: 0440245923";
  std::string expected_co = "\"The Firm\" by John Grisham, \n      1991 (adult fiction book) \n      ISBN: 0440245923\n      Checked out to Professor Rice (817-555-1212)";

  std::string name = "Professor Rice";
  std::string number = "817-555-1212";

  Patron patron(name, number);

  bool passed = true;

  //
  // Test constructor
  //

  Publication publication(
     "The Firm", 
     "John Grisham", 
     "1991", 
     Genre::fiction,
     Media::book,
     Age::adult,
     "0440245923"
  );

  if (publication.to_string() != expected) {
    std::cerr << "Constructor fail: got '" << std::endl
         <<  publication.to_string() 
         << "' but expecting '" << std::endl
         << expected << "'" << std::endl;
    passed = false;
  }

  //
  // Test check_out(patron)
  //
  publication.check_out(patron);

  if (!publication.is_checked_out()) {
    std::cerr << "is_checked_out() reported false after check_out(patron)" << std::endl;
    passed = false;
  }
    
  if (publication.to_string() != expected_co) {
    std::cerr << "Check out fail: got '" << std::endl
         << publication.to_string() 
         << "' but expecting '" << std::endl
         << expected_co << "'" << std::endl;
    passed = false;
  }

  //
  // Test check_in()
  //

  publication.check_in();

  if (publication.is_checked_out()) {
    std::cerr << "is_checked_out() reported true after check_in()" << std::endl;
    passed = false;
  }
    
  if (publication.to_string() != expected) {
    std::cerr << "Check in fail: got '" << std::endl
         << publication.to_string() 
         << "' but expecting '" << std::endl
         << expected << "'" << std::endl;
    passed = false;
  }

  //
  // Report results
  //

  if (!passed) {
    std::cerr << "fail" << std::endl;
    return -1;
  }

  return 0;
}
