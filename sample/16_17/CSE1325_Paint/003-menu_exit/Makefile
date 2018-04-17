CXXFLAGS = --std=c++11

all: div main

rebuild: clean all

debug: CXXFLAGS += -g
debug: rebuild

main: main.o mainwin.o line.o view.o *.h
	$(CXX) $(CXXFLAGS) -o paint main.o mainwin.o line.o view.o `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
main.o: main.cpp *.h
	$(CXX) $(CXXFLAGS) -c main.cpp `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
mainwin.o: mainwin.cpp *.h
	$(CXX) $(CXXFLAGS) -c mainwin.cpp `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
view.o: view.cpp *.h
	$(CXX) $(CXXFLAGS) -c view.cpp `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
line.o: line.cpp *.h
	$(CXX) $(CXXFLAGS) -c line.cpp
clean:
	-rm -f *.o paint
div:
	@echo
	@echo 'X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-'
	@echo '-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X'
	@echo 'X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-'
	@echo '-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X'
	@echo
