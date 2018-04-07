# Makefile for Library Management System
CXXFLAGS += --std=c++14
GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`

all: div main
rebuild: div all

debug: CXXFLAGS += -g
debug: rebuild

main: main.o main_window.o controller.o view.o library.o publication.o patron.o dialogs.o
	$(CXX) $(CXXFLAGS) -o lms main.o main_window.o controller.o view.o library.o publication.o patron.o dialogs.o $(GTKFLAGS)
main.o: main.cpp *.h
	$(CXX) $(CXXFLAGS) -c main.cpp $(GTKFLAGS)
main_window.o: main_window.cpp *.h
	$(CXX) $(CXXFLAGS) -c main_window.cpp $(GTKFLAGS)
controller.o: controller.cpp *.h
	$(CXX) $(CXXFLAGS) -c controller.cpp $(GTKFLAGS)
view.o: view.cpp dialogs.o *.h
	$(CXX) $(CXXFLAGS) -c view.cpp $(GTKFLAGS)
test_library: test_library.o library.o patron.o publication.o view.o
	$(CXX) $(CXXFLAGS) -o test_library test_library.cpp library.o patron.o publication.o
test_library.o: test_library.cpp *.h
	$(CXX) $(CXXFLAGS) -c test_library.cpp
library.o: library.cpp *.h
	$(CXX) $(CXXFLAGS) -c library.cpp
test_publication: test_publication.o publication.o patron.o
	$(CXX) $(CXXFLAGS) -o test_publication test_publication.o publication.o patron.o
test_publication.o: test_publication.cpp *.h
	$(CXX) $(CXXFLAGS) -c test_publication.cpp
publication.o: publication.cpp *.h
	$(CXX) $(CXXFLAGS) -c publication.cpp
test_patron: test_patron.o patron.o
	$(CXX) $(CXXFLAGS) -o test_patron test_patron.o patron.o
test_patron.o: test_patron.cpp *.h
	$(CXX) $(CXXFLAGS) -c test_patron.cpp
patron.o: patron.cpp *.h
	$(CXX) $(CXXFLAGS) -c patron.cpp
dialogs.o: dialogs.cpp *.h
	$(CXX) $(CXXFLAGS) -c dialogs.cpp $(GTKFLAGS)
clean:
	-rm -f *.o lms test_age test_genre test_media test_publication test_patron test_library 
div:
	@echo
	@echo 'X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-'
	@echo '-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X'
	@echo 'X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-'
	@echo '-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X'
	@echo
