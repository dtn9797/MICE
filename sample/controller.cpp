#include "controller.h"
#include "view.h"
#include "library.h"
#include "publication.h"
#include "book.h"
#include "periodical.h"
#include "newspaper.h"
#include "audio.h"
#include "video.h"
#include "patron.h"
#include "genre.h"
#include "media.h"
#include "age.h"
#include <iostream>
#include <string>

using namespace std;

void Controller::cli() {
  int cmd = -1;
  while (cmd != 0) {
    view.show_menu();
    cout << "Command? ";
    cin >> cmd;
    cin.ignore(); // consume \n
    execute_cmd(cmd);
  }
}

void Controller::execute_cmd(int cmd) {
  if (cmd == 1) { // Add publication
    string title, author, copyright, isbn, city;
    int genre, media, age, special;

    cout << "Title? ";
    getline(cin, title);

    cout << "Author? ";
    getline(cin, author);

    cout << "Copyright date? ";
    getline(cin, copyright);

    for (int i = 0; i < Genre::num_genres; ++i) 
      cout << "  " << i << ") " << Genre(i).to_string() << endl;
    cout << "Genre? ";
    cin >> genre;
    cin.ignore(); // consume \n

    for (int i = 0; i < Media::num_media; ++i) 
      cout << "  " << i << ") " << Media(i).to_string() << endl;
    cout << "Media? ";
    cin >> media;
    cin.ignore(); // consume \n

    for (int i = 0; i < Age::num_ages; ++i) 
      cout << "  " << i << ") " << Age(i).to_string() << endl;
    cout << "Age? ";
    cin >> age;
    cin.ignore(); // consume \n

    cout << "ISBN? ";
    getline(cin, isbn);

    switch(media) {
      case Media::book :
          cout << "  1) Hardcover\n  2) Paperback\nEdition? ";
          cin >> special;
          cin.ignore(); // consume \n
          library.add_publication(new Book(title, author, copyright, 
             genre, media, age, isbn, special == 1));
          break;
      case Media::periodical :
          cout << "  1) Weekly\n  2) Monthly\n  3) Quarterly\nFrequency? ";
          cin >> special;
          cin.ignore(); // consume \n
          library.add_publication(new Periodical(title, author, copyright, 
             genre, media, age, isbn, special == 1, special == 2));
          break;
      case Media::newspaper :
          cout << "City? ";
          cin >> city;
          library.add_publication(new Newspaper(title, author, copyright,
             genre, media, age, isbn, city));
          break;
      case Media::audio :
          cout << "  1) MP3\n  2) CD\n  3) cassette\nMedia? ";
          cin >> special;
          cin.ignore(); // consume \n
          library.add_publication(new Audio(title, author, copyright,
             genre, media, age, isbn, special == 1, special == 2));
          break;
      case Media::video:
          cout << "  1) MP4\n  2) DVD\n  3) Bluray\n  4) VHS\nMedia? ";
          cin >> special;
          cin.ignore(); // consume \n
          library.add_publication(new Video(title, author, copyright,
             genre, media, age, isbn, special == 1, special == 2, special == 3));
          break;
      default:
          cerr << "##### Invalid media type" << endl;
    }
 } else if (cmd == 2) { // List all publications
    view.list_publications();

 } else if (cmd == 3) { // Check out publication
    int pub, pat;

    view.list_publications();
    cout << "Publication number? ";
    cin >> pub;
    cin.ignore(); // consume \n

    view.list_patrons();
    cout << "Patron number? ";
    cin >> pat;
    cin.ignore(); // consume \n

    library.check_out(pub, pat);
    
 } else if (cmd == 4) { // Check in publication
    int pub;
    view.list_publications();
    cout << "Publication number? ";
    cin >> pub;
    cin.ignore(); // consume \n

    library.check_in(pub);

 } else if (cmd == 5) { // Add patron
    string name, number;

    cout << "Name? ";
    getline(cin, name);
    cout << "Phone number? ";
    getline(cin, number);
    library.add_patron(Patron(name, number));
    
 } else if (cmd == 6) { // List all patrons
    view.list_patrons();

 } else if (cmd == 9) { // Help
    view.help();
 } else if (cmd == 0) { // Exit
 } else if (cmd == 99) { // Easter Egg
   library.easter_egg();
 } else {
   cerr << "**** Invalid command - type 9 for help" << endl << endl;
 }
}

