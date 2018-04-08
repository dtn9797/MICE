#include "controller.h"
#include <iostream>
#include <string>
#include "topping.h"
#include "scoop.h"
#include "container.h"

using namespace std;

void Controller::cli () {
  int cmd = -1;
  while (cmd != 0) {
    view.show_menu();
    cout << "Command? ";
    cin >> cmd;
    cin.ignore(); // consume \n
    execute_cmd(cmd);
  } 
}

void Controller::execute_cmd (int cmd){
 if (cmd == 1) { // Add scoop
    string name, description;
    double wholesale_cost,retail_price;
    int stock_remaining;

    cout << "Name? ";
    getline(cin, name);

    cout << "Description? ";
    getline(cin, description);

    cout << "Wholesale cost? ";
    cin>>wholesale_cost;
    cin.ignore();

    cout << "retail_price? ";
    cin>>retail_price;
    cin.ignore();

   // cout << "stock_remaining? ";
   // cin>>stock_remaining;
   // cin.ignore();

    emporium.add_scoop(new Scoop(name, description,wholesale_cost,retail_price));
}

 else if (cmd == 2) { // List all scoops
    view.list_scoops();
 }
 else if (cmd == 3) { // Add container
    string name, description;
    double wholesale_cost,retail_price;
    int stock_remaining;
    int scoop_limit;

    cout << "Name? ";
    getline(cin, name);

    cout << "Description? ";
    getline(cin, description);

    cout << "Wholesale cost? ";
    cin>>wholesale_cost;
    cin.ignore();

    cout << "retail_price? ";
    cin>>retail_price;
    cin.ignore();

   // cout << "stock_remaining? ";
   // cin>>stock_remaining;
   // cin.ignore();

    cout << "scoop_limit? ";
    cin>>scoop_limit;
    cin.ignore();


    emporium.add_container(new Container(name, description,wholesale_cost,retail_price,scoop_limit));
}

 else if (cmd == 4) { // List all containers
    view.list_containers();
 }
 else if (cmd == 5) { // Add topping
    string name, description;
    double wholesale_cost,retail_price;
    int stock_remaining;

    cout << "Name? ";
    getline(cin, name);

    cout << "Description? ";
    getline(cin, description);

    cout << "Wholesale cost? ";
    cin>>wholesale_cost;
    cin.ignore();

    cout << "retail_price? ";
    cin>>retail_price;
    cin.ignore();

   // cout << "stock_remaining? ";
   // cin>>stock_remaining;
   // cin.ignore();

    emporium.add_top(new Topping(name, description,wholesale_cost,retail_price));
}

 else if (cmd == 6) { // List all toppings
    view.list_toppings();
 }
//ADD USING DIALOGS
/*if (cmd == 1) { // Add publication
    std::string title, author, copyright, isbn;
    int genre, media, age;

    Gtk::Dialog *dialog = new Gtk::Dialog();
    dialog->set_title("Create Publication");

    // Title
    Gtk::HBox b_title;

    Gtk::Label l_title{"Title:"};
    l_title.set_width_chars(15);
    b_title.pack_start(l_title, Gtk::PACK_SHRINK);

    Gtk::Entry e_title;
    e_title.set_max_length(50);
    b_title.pack_start(e_title, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_title, Gtk::PACK_SHRINK);

    // Author
    Gtk::HBox b_author;

    Gtk::Label l_author{"Author:"};
    l_author.set_width_chars(15);
    b_author.pack_start(l_author, Gtk::PACK_SHRINK);

    Gtk::Entry e_author;
    e_author.set_max_length(50);
    b_author.pack_start(e_author, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_author, Gtk::PACK_SHRINK);

    // Copyright date
    Gtk::HBox b_copyright;

    Gtk::Label l_copyright{"Copyright date:"};
    l_copyright.set_width_chars(15);
    b_copyright.pack_start(l_copyright, Gtk::PACK_SHRINK);

    Gtk::Entry e_copyright;
    e_copyright.set_max_length(50);
    b_copyright.pack_start(e_copyright, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_copyright, Gtk::PACK_SHRINK);

    // Age
    Gtk::HBox b_age;

    Gtk::Label l_age{"Age:"};
    l_age.set_width_chars(15);
    b_age.pack_start(l_age, Gtk::PACK_SHRINK);

    Gtk::ComboBoxText c_age;
    c_age.set_size_request(160);
    c_age.append("Children");
    c_age.append("Teen");
    c_age.append("Adult");
    c_age.append("Restricted");
    b_age.pack_start(c_age, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_age, Gtk::PACK_SHRINK);

    // Genre
    Gtk::HBox b_genre;

    Gtk::Label l_genre{"Genre:"};
    l_genre.set_width_chars(15);
    b_genre.pack_start(l_genre, Gtk::PACK_SHRINK);

    Gtk::ComboBoxText c_genre;
    c_genre.set_size_request(160);
    c_genre.append("Fiction");
    c_genre.append("Non-fiction");
    c_genre.append("Self Help");
    c_genre.append("Performance");
    b_genre.pack_start(c_genre, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_genre, Gtk::PACK_SHRINK);

    // Media
    Gtk::HBox b_media;

    Gtk::Label l_media{"Media:"};
    l_media.set_width_chars(15);
    b_media.pack_start(l_media, Gtk::PACK_SHRINK);

    Gtk::ComboBoxText c_media;
    c_media.set_size_request(160);
    c_media.append("Book");
    c_media.append("Periodical");
    c_media.append("Newspaper");
    c_media.append("Audio");
    c_media.append("Video");
    b_media.pack_start(c_media, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_media, Gtk::PACK_SHRINK);

    // ISBN
    Gtk::HBox b_isbn;

    Gtk::Label l_isbn{"ISBN:"};
    l_isbn.set_width_chars(15);
    b_isbn.pack_start(l_isbn, Gtk::PACK_SHRINK);

    Gtk::Entry e_isbn;
    e_isbn.set_max_length(50);
    b_isbn.pack_start(e_isbn, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_isbn, Gtk::PACK_SHRINK);

    // Show dialog
    dialog->add_button("Cancel", 0);
    dialog->add_button("OK", 1);
    dialog->show_all();
    int result = dialog->run();

    dialog->close();
    while (Gtk::Main::events_pending())  Gtk::Main::iteration();

    title = e_title.get_text();
    author = e_author.get_text();
    copyright = e_copyright.get_text();
    age = c_age.get_active_row_number();
    genre = c_genre.get_active_row_number();
    media = c_media.get_active_row_number();
    isbn = e_isbn.get_text();

    if (result == 1)
      library.add_publication(Publication(title, author, copyright, genre, media, age, isbn));
*/
}
