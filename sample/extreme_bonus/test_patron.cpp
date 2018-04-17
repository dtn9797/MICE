#include "patron.h"

int main() {
  std::string name = "Professor Rice";
  std::string number = "817-555-1212";

  bool passed = true;

  Patron p(name, number);

  if (p.get_patron_name() != name) {
    std::cerr << "Name was '" << p.get_patron_name() << 
          "' should be '" << name << "'" << std::endl;
    passed = false;
  }

  if (p.get_patron_phone_number() != number) {
    std::cerr << "Number was '" << p.get_patron_phone_number()  << 
          "' should be '" << number << "'" << std::endl;
    passed = false;
  }

  std::string expected = "Professor Rice (817-555-1212)";
  if (p.to_string() != expected) {
    std::cerr << "to_string was '" << p.to_string() <<
            "' but should be '" << expected << std::endl;
    passed = false;
  }

  if (!passed) {
    std::cerr << "fail" << std::endl;
    return -1;
  }
  return 0;
}
