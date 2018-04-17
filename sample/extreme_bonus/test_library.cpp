#include "patron.h"
#include "publication.h"
#include "library.h"

int main() {
  Library library;

  bool passed = true;

  //
  // Test adding patrons
  //
  Patron larry("Larry", "817-555-1111");
  Patron curly("Curly", "817-555-2222");
  Patron moe("Moe", "817-555-3333");

  if (library.number_of_patrons() != 0) {
    passed = false;
    std::cerr << "Started with " << library.number_of_patrons() << " patrons" << std::endl;
  }

  library.add_patron(larry);
  library.add_patron(curly);
  library.add_patron(moe);

  if (library.number_of_patrons() != 3) {
    passed = false;
    std::cerr << "Ended with " << library.number_of_patrons() << " patrons (expected 3)" << std::endl;
  }

  if (library.patron_to_string(2) != "Moe (817-555-3333)") {
    passed = false;
    std::cerr << "Patron 3 is " << library.patron_to_string(2) << " (not Moe)" << std::endl;
  }

  //
  // Test adding publications
  //

  Publication foundation("Foundation", "Isaac Asimov", "1942", 
      Genre::fiction, Media::book, Age::adult, "0385177259");
  Publication foundation_empire("Foundation and Empire", "Isaac Asimov", "1943", 
      Genre::fiction, Media::book, Age::adult, "0385177259");
  Publication foundation2("Second Foundation", "Isaac Asimov", "1944", 
      Genre::fiction, Media::book, Age::adult, "0385177259");
  Publication war("War of the Worlds", "Jeff Wayne", "1977",
      Genre::performance, Media::audio, Age::teen, "9780711969148");
  Publication wonka("Willy Wonka and the Chocolate Factory", "Roald Dahl", "1971",
      Genre::performance, Media::video, Age::children, "0142410314");

  if (library.number_of_publications() != 0) {
    passed = false;
    std::cerr << "Started with " << library.number_of_publications() << " publications" << std::endl;
  }

  library.add_publication(foundation);
  library.add_publication(foundation_empire);
  library.add_publication(foundation2);
  library.add_publication(war);
  library.add_publication(wonka);

  if (library.number_of_publications() != 5) {
    passed = false;
    std::cerr << "ended with " << library.number_of_publications() << " publications (expected 5)" << std::endl;
  }

  std::string expected = "\"Foundation\" by Isaac Asimov, \n      1942 (adult fiction book) \n      ISBN: 0385177259";
  if (library.publication_to_string(0) != expected) {
    passed = false;
    std::cerr << "Foundation string from publication_to_string doesn't match" << std::endl;
    std::cerr << "expected: " << std::endl
              << expected 
              << "actual: " << std::endl
              << library.publication_to_string(0) << std::endl;
  }

  //
  // Test check out and check in
  //

  library.check_out(1, 1);

  expected = "\"Foundation and Empire\" by Isaac Asimov, \n      1943 (adult fiction book) \n      ISBN: 0385177259\n      Checked out to Curly (817-555-2222)";
  std::string actual = library.publication_to_string(1);
  if (actual != expected) {
    passed = false;
    std::cerr << "String from publication_to_string doesn't match after check out" << std::endl;
    std::cerr << "  Expected: " << std::endl
              << expected << std::endl;
    std::cerr << "  Actual:   " << std::endl
              << actual << std::endl;
  }

  library.check_in(1);
  expected = "\"Foundation and Empire\" by Isaac Asimov, \n      1943 (adult fiction book) \n      ISBN: 0385177259";
  actual = library.publication_to_string(1);
  if (actual != expected) {
    passed = false;
    std::cerr << "String from publication_to_string doesn't match after check in" << std::endl;
    std::cerr << "  Expected: " << std::endl
              << expected << std::endl;
    std::cerr << "  Actual:   " << std::endl
              << actual << std::endl;
  }


  //
  // Show results
  //
  if (!passed) {
    std::cerr << "fail" << std::endl;
    return -1;
  }

  return 0;
}
