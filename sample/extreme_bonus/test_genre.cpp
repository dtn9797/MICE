#include "genre.h"
#include <iostream>

int main() {

  Genre m1(Genre::performance);
  if (m1.to_string() != "performance") {
    std::cerr << "performance failed: got " << m1.to_string() << std::endl;
    return 1;
  }

  return 0;
}
